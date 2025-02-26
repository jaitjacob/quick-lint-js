// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <quick-lint-js/array.h>
#include <quick-lint-js/cli/cli-location.h>
#include <quick-lint-js/container/concat.h>
#include <quick-lint-js/container/padded-string.h>
#include <quick-lint-js/diag-collector.h>
#include <quick-lint-js/diag-matcher.h>
#include <quick-lint-js/diag/diagnostic-types.h>
#include <quick-lint-js/fe/language.h>
#include <quick-lint-js/fe/parse.h>
#include <quick-lint-js/parse-support.h>
#include <quick-lint-js/port/char8.h>
#include <quick-lint-js/spy-visitor.h>
#include <string>
#include <string_view>
#include <vector>

using ::testing::ElementsAreArray;

namespace quick_lint_js {
namespace {
class Test_Parse_TypeScript_Declare_TSModule : public Test_Parse_Expression {};

TEST_F(Test_Parse_TypeScript_Declare_TSModule, declare_module) {
  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'my name space' {}"_sv, no_diags, typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",    //
                              "visit_enter_namespace_scope",  // {
                              "visit_exit_namespace_scope",   // }
                              "visit_exit_declare_scope",     //
                              "visit_end_of_module",
                          }));
  }
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule, declare_module_permits_no_body) {
  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'my name space';"_sv, no_diags, typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",  //
                              "visit_exit_declare_scope",   //
                              "visit_end_of_module",
                          }));
  }

  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'my name space'"_sv, no_diags, typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",  //
                              "visit_exit_declare_scope",   //
                              "visit_end_of_module",
                          }));
  }

  {
    // ASI
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'my name space'\nhello;"_sv, no_diags,
        typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",  //
                              "visit_exit_declare_scope",   //
                              "visit_variable_use",         // hello
                              "visit_end_of_module",
                          }));
  }

  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'my name space' /*;*/ declare class C {}"_sv,
        u8"                              ` Diag_Missing_Semicolon_After_Statement"_diag,
        typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",     //
                              "visit_exit_declare_scope",      //
                              "visit_enter_declare_scope",     //
                              "visit_enter_class_scope",       // C
                              "visit_enter_class_scope_body",  // {
                              "visit_exit_class_scope",        // }
                              "visit_variable_declaration",    // C
                              "visit_exit_declare_scope",      //
                              "visit_end_of_module",
                          }));
  }
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule,
       declaring_module_is_not_allowed_inside_containing_namespace) {
  test_parse_and_visit_module(
      u8"namespace ns { declare module 'my name space' {} }"_sv,  //
      u8"                              ^^^^^^^^^^^^^^^ Diag_String_Namespace_Name_Not_Allowed_In_Namespace"_diag,  //
      typescript_options);

  test_parse_and_visit_module(
      u8"declare namespace ns { module 'inner ns' { } }"_sv,  //
      u8"                              ^^^^^^^^^^ Diag_String_Namespace_Name_Not_Allowed_In_Namespace"_diag,  //
      typescript_options);
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule,
       declaring_module_is_allowed_inside_containing_module) {
  test_parse_and_visit_module(
      u8"declare module 'outer' { module 'inner' {} }"_sv, no_diags,
      typescript_options);
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule,
       declare_module_allows_import_from_module) {
  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'mymod' { import fs from 'fs'; }"_sv, no_diags,
        typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",    //
                              "visit_enter_namespace_scope",  // {
                              "visit_variable_declaration",   // fs
                              "visit_exit_namespace_scope",   // }
                              "visit_exit_declare_scope",     //
                              "visit_end_of_module",          //
                          }));
  }

  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'mymod' { import fs = require('fs'); }"_sv, no_diags,
        typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",    //
                              "visit_enter_namespace_scope",  // {
                              "visit_variable_declaration",   // fs
                              "visit_exit_namespace_scope",   // }
                              "visit_exit_declare_scope",     //
                              "visit_end_of_module",          //
                          }));
  }
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule,
       declare_module_allows_import_from_module_with_export_keyword) {
  test_parse_and_visit_module(
      u8"declare module 'mymod' { export * from 'module'; }"_sv, no_diags,
      typescript_options);

  test_parse_and_visit_module(
      u8"declare module 'mymod' { export {Z} from 'module'; }"_sv, no_diags,
      typescript_options);
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule,
       declare_module_allows_exporting_default) {
  test_parse_and_visit_module(
      u8"declare module 'mymod' { export default class C {} }"_sv, no_diags,
      typescript_options);

  test_parse_and_visit_module(
      u8"declare module 'mymod' { export default function f(); }"_sv, no_diags,
      typescript_options);
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule,
       export_default_of_variable_is_allowed_in_declare_module) {
  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'mymod' { export default Z; }"_sv, no_diags,
        typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",          //
                              "visit_enter_namespace_scope",        // {
                              "visit_variable_export_default_use",  // Z
                              "visit_exit_namespace_scope",         // }
                              "visit_exit_declare_scope",           //
                              "visit_end_of_module",                //
                          }));
  }

  // See also Test_Parse_Module
  // export_default_with_contextual_keyword_variable_expression.
  Dirty_Set<String8> variable_names =
      // TODO(#73): Disallow 'interface'.
      // TODO(#73): Disallow 'protected', 'implements', etc.
      // (strict_only_reserved_keywords).
      (contextual_keywords - Dirty_Set<String8>{u8"let", u8"interface"}) |
      Dirty_Set<String8>{u8"await", u8"yield"};
  for (String8_View variable_name : variable_names) {
    Test_Parser p(concat(u8"declare module 'mymod' { export default "_sv,
                         variable_name, u8"; }"_sv),
                  typescript_options);
    SCOPED_TRACE(p.code);
    p.parse_and_visit_module();
    EXPECT_THAT(p.visits,
                ElementsAreArray({
                    "visit_enter_declare_scope",          //
                    "visit_enter_namespace_scope",        // {
                    "visit_variable_export_default_use",  // (variable_name)
                    "visit_exit_namespace_scope",         // {
                    "visit_exit_declare_scope",           //
                    "visit_end_of_module",                //
                }));
    EXPECT_THAT(p.variable_uses, ElementsAreArray({variable_name}));
  }

  // See also Test_Parse_Module
  // export_default_async_function_with_newline_inserts_semicolon.
  {
    Spy_Visitor p = test_parse_and_visit_module(
        u8"declare module 'mymod' { export default async\nfunction f(); }"_sv,
        no_diags, typescript_options);
    EXPECT_THAT(p.visits, ElementsAreArray({
                              "visit_enter_declare_scope",          //
                              "visit_enter_namespace_scope",        // {
                              "visit_variable_export_default_use",  // async
                              "visit_enter_function_scope",         // f
                              "visit_exit_function_scope",          // f
                              "visit_variable_declaration",         // f
                              "visit_exit_namespace_scope",         // {
                              "visit_exit_declare_scope",           //
                              "visit_end_of_module",                //
                          }));
    EXPECT_THAT(p.variable_uses, ElementsAreArray({u8"async"}));
  }
}

TEST_F(Test_Parse_TypeScript_Declare_TSModule,
       default_exports_in_different_modules_are_allowed) {
  test_parse_and_visit_module(
      u8"declare module 'a' {\n"_sv
      u8"  export default class C {}\n"_sv
      u8"}\n"_sv
      u8"declare module 'b' {\n"_sv
      u8"  export default class C {}\n"_sv
      u8"}\n"_sv,
      no_diags, typescript_options);
}
}
}

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew "strager" Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
