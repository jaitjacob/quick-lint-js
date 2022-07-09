// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#if defined(__EMSCRIPTEN__)
// No LSP on the web.
#else

#include <boost/json/value.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <quick-lint-js/boost-json.h>
#include <quick-lint-js/byte-buffer.h>
#include <quick-lint-js/lsp-workspace-configuration.h>
#include <quick-lint-js/parse-json.h>
#include <simdjson.h>
#include <string>
#include <string_view>
#include <utility>

using ::testing::IsEmpty;
using namespace std::literals::string_view_literals;

namespace quick_lint_js {
namespace {
struct easy_simdjson_parser {
  explicit easy_simdjson_parser(::simdjson::padded_string json)
      : error(::simdjson::TAPE_ERROR),  // Arbitrary non-successful error code.
        json(std::move(json)) {
    this->error = parser.iterate(this->json).get(this->document);
    if (this->error != ::simdjson::SUCCESS) {
      return;
    }
    this->error = this->document.get_value().get(this->value);
  }

  ::simdjson::error_code error;
  ::simdjson::padded_string json;
  ::simdjson::ondemand::parser parser;
  ::simdjson::ondemand::document document;
  ::simdjson::ondemand::value value;
};

TEST(test_lsp_workspace_configuration, empty_config_request) {
  lsp_workspace_configuration config;

  byte_buffer request_json;
  config.build_request(77, request_json);

  ::boost::json::value request = parse_boost_json(request_json);
  EXPECT_EQ(look_up(request, "jsonrpc"), "2.0");
  EXPECT_EQ(look_up(request, "id"), 77);
  EXPECT_EQ(look_up(request, "method"), "workspace/configuration");
  ::boost::json::array items = look_up(request, "params", "items").as_array();
  EXPECT_THAT(items, IsEmpty());
}

TEST(test_lsp_workspace_configuration, config_request_with_three_items) {
  std::string items[3];
  lsp_workspace_configuration config;
  config.add_item(u8"first"sv, &items[0]);
  config.add_item(u8"second"sv, &items[1]);
  config.add_item(u8"third"sv, &items[2]);

  byte_buffer request_json;
  config.build_request(77, request_json);

  ::boost::json::value request = parse_boost_json(request_json);
  ::boost::json::array request_items =
      look_up(request, "params", "items").as_array();
  ASSERT_EQ(request_items.size(), 3);
  EXPECT_EQ(look_up(request_items[0], "section"), "first");
  EXPECT_EQ(look_up(request_items[1], "section"), "second");
  EXPECT_EQ(look_up(request_items[2], "section"), "third");
}

TEST(test_lsp_workspace_configuration, empty_config_response) {
  lsp_workspace_configuration config;

  easy_simdjson_parser result("[]"_padded);
  ASSERT_EQ(result.error, ::simdjson::SUCCESS);
  bool ok = config.process_response(result.value);
  ASSERT_TRUE(ok);
}

TEST(test_lsp_workspace_configuration, config_response_with_strings) {
  std::string items[3];
  lsp_workspace_configuration config;
  config.add_item(u8"first"sv, &items[0]);
  config.add_item(u8"second"sv, &items[1]);
  config.add_item(u8"third"sv, &items[2]);

  easy_simdjson_parser result(
      R"(["firstval", "secondval", "thirdval"])"_padded);
  ASSERT_EQ(result.error, ::simdjson::SUCCESS);
  bool ok = config.process_response(result.value);
  ASSERT_TRUE(ok);

  EXPECT_EQ(items[0], "firstval");
  EXPECT_EQ(items[1], "secondval");
  EXPECT_EQ(items[2], "thirdval");
}

TEST(test_lsp_workspace_configuration,
     empty_config_response_with_added_items_fails) {
  std::string myitem = "originalvalue";
  lsp_workspace_configuration config;
  config.add_item(u8"myitem"sv, &myitem);

  easy_simdjson_parser result("[]"_padded);
  ASSERT_EQ(result.error, ::simdjson::SUCCESS);
  bool ok = config.process_response(result.value);
  ASSERT_FALSE(ok);

  EXPECT_EQ(myitem, "originalvalue") << "item should not change value";
}

TEST(test_lsp_workspace_configuration,
     more_values_than_config_fails_but_sets_values_anyway) {
  std::string myitem;
  lsp_workspace_configuration config;
  config.add_item(u8"myitem"sv, &myitem);

  easy_simdjson_parser result(R"(["val", "otherval"])"_padded);
  ASSERT_EQ(result.error, ::simdjson::SUCCESS);
  bool ok = config.process_response(result.value);
  ASSERT_FALSE(ok);

  EXPECT_EQ(myitem, "val");
}

TEST(test_lsp_workspace_configuration, null_clears_string) {
  std::string myitem = "hello";
  lsp_workspace_configuration config;
  config.add_item(u8"myitem"sv, &myitem);

  easy_simdjson_parser result(R"([null])"_padded);
  ASSERT_EQ(result.error, ::simdjson::SUCCESS);
  bool ok = config.process_response(result.value);
  EXPECT_TRUE(ok);

  EXPECT_EQ(myitem, "");
}

TEST(test_lsp_workspace_configuration, non_array_config_response_fails) {
  lsp_workspace_configuration config;

  easy_simdjson_parser result("{}"_padded);
  ASSERT_EQ(result.error, ::simdjson::SUCCESS);
  bool ok = config.process_response(result.value);
  ASSERT_FALSE(ok);
}
}
}

#endif

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
