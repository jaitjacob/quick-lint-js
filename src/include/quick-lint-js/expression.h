// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew Glazar
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef QUICK_LINT_JS_EXPRESSION_H
#define QUICK_LINT_JS_EXPRESSION_H

#include <deque>
#include <memory>
#include <quick-lint-js/buffering-visitor.h>
#include <quick-lint-js/lex.h>
#include <quick-lint-js/location.h>
#include <quick-lint-js/narrow-cast.h>
#include <type_traits>
#include <utility>
#include <vector>

namespace quick_lint_js {
class expression;

class expression_ptr {
 public:
  explicit expression_ptr(expression *ptr) noexcept : ptr_(ptr) {}

  expression *operator->() const noexcept { return this->ptr_; }
  expression &operator*() const noexcept { return *this->ptr_; }

  bool operator==(expression_ptr other) const noexcept {
    return this->ptr_ == other.ptr_;
  }

  bool operator!=(expression_ptr other) const noexcept {
    return !(*this == other);
  }

 private:
  expression *ptr_;
};

enum class expression_kind {
  _invalid,
  _new,
  _template,
  assignment,
  await,
  binary_operator,
  call,
  dot,
  function,
  literal,
  named_function,
  unary_operator,
  variable,
};

class expression {
 public:
  template <expression_kind Kind>
  struct tag {};

  explicit expression(tag<expression_kind::_invalid>) noexcept
      : kind_(expression_kind::_invalid) {}

  explicit expression(tag<expression_kind::_new>,
                      std::vector<expression_ptr> &&children,
                      source_code_span span) noexcept
      : kind_(expression_kind::_new),
        span_(span),
        children_(std::move(children)) {}

  explicit expression(tag<expression_kind::_template>,
                      std::vector<expression_ptr> &&children,
                      source_code_span span) noexcept
      : kind_(expression_kind::_template),
        span_(span),
        children_(std::move(children)) {}

  explicit expression(tag<expression_kind::assignment>, expression_ptr lhs,
                      expression_ptr rhs) noexcept
      : kind_(expression_kind::assignment), children_{lhs, rhs} {}

  explicit expression(tag<expression_kind::await>, expression_ptr child,
                      source_code_span operator_span) noexcept
      : kind_(expression_kind::await),
        unary_operator_begin_(operator_span.begin()),
        children_{child} {}

  explicit expression(tag<expression_kind::binary_operator>,
                      std::vector<expression_ptr> &&children) noexcept
      : kind_(expression_kind::binary_operator),
        children_(std::move(children)) {}

  explicit expression(tag<expression_kind::call>,
                      std::vector<expression_ptr> &&children,
                      source_code_span span) noexcept
      : kind_(expression_kind::call),
        call_right_paren_end_(span.end()),
        children_(std::move(children)) {}

  explicit expression(tag<expression_kind::dot>, expression_ptr lhs,
                      identifier rhs) noexcept
      : kind_(expression_kind::dot),
        variable_identifier_(rhs),
        children_{lhs} {}

  explicit expression(tag<expression_kind::function>,
                      std::unique_ptr<buffering_visitor> &&child_visits,
                      source_code_span span) noexcept
      : kind_(expression_kind::function),
        span_(span),
        child_visits_(std::move(child_visits)) {}

  explicit expression(tag<expression_kind::literal>,
                      source_code_span span) noexcept
      : kind_(expression_kind::literal), span_(span) {}

  explicit expression(tag<expression_kind::named_function>, identifier name,
                      source_code_span span) noexcept
      : kind_(expression_kind::named_function),
        variable_identifier_(name),
        span_(span) {}

  explicit expression(tag<expression_kind::unary_operator>,
                      expression_ptr child,
                      source_code_span operator_span) noexcept
      : kind_(expression_kind::unary_operator),
        unary_operator_begin_(operator_span.begin()),
        children_{child} {}

  explicit expression(tag<expression_kind::variable>,
                      identifier variable_identifier) noexcept
      : kind_(expression_kind::variable),
        variable_identifier_(variable_identifier) {}

  expression_kind kind() const noexcept { return this->kind_; }

  identifier variable_identifier() const noexcept {
    switch (this->kind_) {
      case expression_kind::dot:
      case expression_kind::named_function:
      case expression_kind::variable:
        break;
      default:
        assert(false);
        break;
    }
    return this->variable_identifier_;
  }

  int child_count() const noexcept {
    switch (this->kind_) {
      case expression_kind::_new:
      case expression_kind::_template:
      case expression_kind::assignment:
      case expression_kind::binary_operator:
      case expression_kind::call:
        break;
      default:
        assert(false);
        break;
    }
    return narrow_cast<int>(this->children_.size());
  }

  expression_ptr child_0() const noexcept { return this->child(0); }

  expression_ptr child_1() const noexcept { return this->child(1); }

  expression_ptr child(int index) const noexcept {
    assert(index >= 0);
    assert(index < static_cast<int>(this->children_.size()));
    return this->children_[index];
  }

  // Can be called at most once.
  template <class Visitor>
  void visit_children(Visitor &v) {
    switch (this->kind_) {
      case expression_kind::function:
      case expression_kind::named_function:
        break;
      default:
        assert(false);
        break;
    }
    assert(
        this->child_visits_ &&
        "visit_children can be called at most once, but it was called twice");
    this->child_visits_->move_into(v);
    this->child_visits_.reset();
  }

  source_code_span span() const noexcept {
    switch (this->kind_) {
      case expression_kind::_invalid:
        assert(false && "Not yet implemented");
        break;
      case expression_kind::_new:
      case expression_kind::_template:
      case expression_kind::function:
      case expression_kind::literal:
      case expression_kind::named_function:
        return this->span_;
      case expression_kind::assignment:
      case expression_kind::binary_operator:
        return source_code_span(this->children_.front()->span().begin(),
                                this->children_.back()->span().end());
      case expression_kind::call:
        return source_code_span(this->children_.front()->span().begin(),
                                this->call_right_paren_end_);
      case expression_kind::dot:
        return source_code_span(this->child_0()->span().begin(),
                                this->variable_identifier_.span().end());
      case expression_kind::await:
      case expression_kind::unary_operator:
        return source_code_span(this->unary_operator_begin_,
                                this->child_0()->span().end());
      case expression_kind::variable:
        return this->variable_identifier_.span();
    }
    __builtin_unreachable();
  }

 private:
  expression_kind kind_;
  union {
    identifier variable_identifier_;  // dot, named_function, variable
    static_assert(std::is_trivially_destructible_v<identifier>);

    const char *call_right_paren_end_;  // call

    const char *unary_operator_begin_;  // await, unary_operator
  };
  union {
    source_code_span
        span_;  // _new, _template, function, literal, named_function
    static_assert(std::is_trivially_destructible_v<source_code_span>);
  };
  std::vector<expression_ptr> children_;
  std::unique_ptr<buffering_visitor> child_visits_;  // function, named_function
};

class expression_arena {
 public:
  template <expression_kind Kind, class... Args>
  expression_ptr make_expression(Args &&... args) {
    this->expressions_.emplace_back(expression::tag<Kind>(),
                                    std::forward<Args>(args)...);
    return expression_ptr(&this->expressions_.back());
  }

 private:
  std::deque<expression> expressions_;
};
}  // namespace quick_lint_js

#endif
