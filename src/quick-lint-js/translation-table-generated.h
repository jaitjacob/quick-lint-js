// Code generated by tools/compile-translations.go. DO NOT EDIT.
// source: po/*.po

// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#ifndef QUICK_LINT_JS_TRANSLATION_TABLE_GENERATED_H
#define QUICK_LINT_JS_TRANSLATION_TABLE_GENERATED_H

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <quick-lint-js/assert.h>
#include <quick-lint-js/consteval.h>
#include <quick-lint-js/hash-fnv.h>
#include <quick-lint-js/translation-table.h>
#include <string_view>

namespace quick_lint_js {
using namespace std::literals::string_view_literals;

constexpr std::uint32_t translation_table_locale_count = 5;
constexpr std::uint16_t translation_table_mapping_table_size = 301;
constexpr std::size_t translation_table_string_table_size = 59622;
constexpr std::size_t translation_table_locale_table_size = 37;

QLJS_CONSTEVAL std::uint16_t translation_table_const_hash_table_look_up(
    std::string_view untranslated) {
  struct const_hash_entry {
    std::uint16_t mapping_table_index;
    const char* untranslated;
  };

  // clang-format off
  constexpr const_hash_entry const_hash_table[] = {
          {126, "expected {1:singular}"},
          {0, ""},
          {243, "stray comma in let statement"},
          {179, "missing body for TypeScript interface"},
          {148, "incomplete export; expected 'export default ...' or 'export {{name}' or 'export * from ...' or 'export class' or 'export function' or 'export let'"},
          {205, "missing name of exported function"},
          {203, "missing name of class"},
          {280, "unmatched indexing bracket"},
          {23, "'with' statement"},
          {15, "'do-while' loop"},
          {54, "a 'for' loop"},
          {33, "JSON syntax error"},
          {75, "cannot access private identifier outside class"},
          {156, "invalid expression left of assignment"},
          {0, ""},
          {55, "a 'while' loop"},
          {122, "expected parameter for arrow function, but got an expression instead"},
          {212, "missing parentheses around self-invoked function"},
          {219, "missing semicolon between condition and update parts of for loop"},
          {9, "'=' changes variables; to compare, use '===' instead"},
          {117, "expected expression after 'case'"},
          {241, "something happened"},
          {0, ""},
          {0, ""},
          {170, "missing ':' in conditional expression"},
          {242, "stray comma in function parameter"},
          {199, "missing header and body for 'for' loop"},
          {123, "expected variable name for 'catch'"},
          {207, "missing operand for operator"},
          {2, "\"global-groups\" must be a boolean or an array"},
          {150, "index signatures require a value type"},
          {56, "a 'with' statement"},
          {43, "TypeScript interface methods cannot contain a body"},
          {77, "cannot declare 'await' inside async function"},
          {151, "indexing requires an expression"},
          {267, "unexpected characters in hex literal"},
          {78, "cannot declare 'yield' inside generator function"},
          {30, "BigInt literal contains exponent"},
          {0, ""},
          {149, "index signature must be a field, not a method"},
          {290, "what is this '{1}' nonsense?"},
          {98, "const fields within classes are only allowed in TypeScript, not JavaScript"},
          {83, "cannot import 'let'"},
          {171, "missing '<>' and '</>' to enclose multiple children"},
          {107, "escaped character is not allowed in identifiers"},
          {217, "missing semicolon after index signature"},
          {0, ""},
          {0, ""},
          {93, "code point out of range"},
          {61, "an 'if' statement"},
          {0, ""},
          {0, ""},
          {234, "private properties are not allowed in object literals"},
          {0, ""},
          {74, "break can only be used inside of a loop or switch"},
          {116, "expected '{{'"},
          {0, ""},
          {0, ""},
          {141, "generator function '*' belongs after keyword function"},
          {32, "C-style for loops have only three semicolon-separated components"},
          {60, "a {{0} b }} c"},
          {129, "extra ',' is not allowed between enum members"},
          {240, "see here"},
          {283, "use 'while' instead to loop until a condition is false"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {65, "assigning to 'async' in a for-of loop requires parentheses"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {50, "TypeScript's 'enum' feature is not allowed in JavaScript"},
          {113, "expected 'as' between '{1}' and '{2}'"},
          {175, "missing arrow operator for arrow function"},
          {0, ""},
          {295, "write a name to declare a class method"},
          {0, ""},
          {90, "classes cannot be named 'await' in async function"},
          {99, "const variable declared here"},
          {0, ""},
          {79, "cannot declare and export variable with 'export default'"},
          {226, "newline is not allowed between 'async' and arrow function parameter list"},
          {0, ""},
          {89, "class methods cannot be optional"},
          {0, ""},
          {8, "'.' operator needs a key name; use + to concatenate strings; use [] to access with a dynamic key"},
          {259, "unexpected '@'"},
          {274, "unexpected statement before first switch case, expected 'case' or 'default'"},
          {130, "extra ',' is not allowed between function call arguments"},
          {157, "invalid function parameter"},
          {105, "enum member name cannot be numeric"},
          {285, "use of undeclared variable: {0}"},
          {165, "methods cannot be readonly"},
          {41, "TypeScript interface methods cannot be marked 'async'"},
          {35, "RegExp literal flags cannot contain Unicode escapes"},
          {245, "switch statement needs parentheses around condition"},
          {291, "while loop is missing '{1}' around condition"},
          {38, "TypeScript call signatures are only allowed in classes"},
          {0, ""},
          {0, ""},
          {296, "{0} classes are not allowed in JavaScript"},
          {184, "missing body for function"},
          {228, "number literal contains trailing underscore(s)"},
          {31, "C-style for loop is missing its third component"},
          {0, ""},
          {246, "this {0} looks fishy"},
          {0, ""},
          {0, ""},
          {67, "assignment to const variable"},
          {91, "classes cannot be named 'let'"},
          {0, ""},
          {124, "expected variable name for 'import'-'as'"},
          {161, "label named 'await' not allowed in async function"},
          {0, ""},
          {0, ""},
          {0, ""},
          {169, "missing '...' in JSX attribute spread"},
          {0, ""},
          {92, "code point in Unicode escape sequence must not be greater than U+10FFFF"},
          {133, "for-of loop expression cannot have semicolons"},
          {186, "missing body for while loop"},
          {159, "invalid lone literal in object literal"},
          {185, "missing body for try statement"},
          {0, ""},
          {0, ""},
          {251, "unclosed code block; expected '}' by end of file"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {88, "children end here"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {84, "cannot import variable named keyword '{0}'"},
          {253, "unclosed interface; expected '}' by end of file"},
          {34, "React/JSX is not yet implemented"},
          {4, "\"globals\" descriptor \"writable\" property must be a boolean"},
          {244, "switch statement is missing '{1}' around condition"},
          {262, "unexpected 'catch' without 'try'"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {76, "cannot assign to loop variable in for of/in loop"},
          {209, "missing parameters for arrow function"},
          {0, ""},
          {20, "'in' disallowed in C-style for loop initializer"},
          {53, "a 'do-while' loop"},
          {0, ""},
          {0, ""},
          {0, ""},
          {1, "\"global-groups\" entries must be strings"},
          {294, "with statement needs parentheses around expression"},
          {80, "cannot declare variable named keyword '{0}'"},
          {0, ""},
          {202, "missing name in function statement"},
          {10, "'>' is not allowed directly in JSX text; write {{'>'} or &gt; instead"},
          {12, "'async static' is not allowed; write 'static async' instead"},
          {213, "missing property name after '.' operator"},
          {0, ""},
          {0, ""},
          {0, ""},
          {136, "function call started here"},
          {0, ""},
          {0, ""},
          {0, ""},
          {239, "return statement returns nothing (undefined)"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {138, "function declared here"},
          {40, "TypeScript interface fields cannot be initalized"},
          {108, "escaping '-' is not allowed in tag names; write '-' instead"},
          {0, ""},
          {0, ""},
          {192, "missing condition for if statement"},
          {101, "depth limit exceeded"},
          {180, "missing body for catch clause"},
          {52, "TypeScript's 'readonly' feature is not allowed in JavaScript code"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {106, "enum member needs initializer"},
          {46, "TypeScript interfaces cannot be named 'await' in async function"},
          {0, ""},
          {0, ""},
          {172, "missing '=' after variable"},
          {187, "missing body for {1:headlinese}"},
          {162, "legacy octal literal may not be BigInt"},
          {231, "octal literal may not have exponent"},
          {196, "missing expression between parentheses"},
          {25, "'{0}' is not allowed for strings; use {1} instead"},
          {235, "redeclaration of global variable"},
          {152, "integer cannot be represented and will be rounded to '{1}'"},
          {0, ""},
          {216, "missing semicolon after field"},
          {275, "unexpected token"},
          {44, "TypeScript interface properties cannot be 'static'"},
          {273, "unexpected literal in parameter list; expected parameter name"},
          {218, "missing semicolon after statement"},
          {221, "missing value for object property"},
          {0, ""},
          {0, ""},
          {233, "opening '<{1}>' tag here"},
          {100, "continue can only be used inside of a loop"},
          {28, "'}' is not allowed directly in JSX text; write {{'}'} instead"},
          {120, "expected hexadecimal digits in Unicode escape sequence"},
          {42, "TypeScript interface methods cannot be marked as a generator"},
          {87, "character is not allowed in identifiers"},
          {0, ""},
          {208, "missing operator between expression and arrow function"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {215, "missing quotes around module name '{0}'"},
          {22, "'while' loop"},
          {59, "a lexical declaration is not allowed as the body of {1:singular}"},
          {128, "exporting requires '{{' and '}'"},
          {237, "redundant delete statement on variable"},
          {7, "'**' operator cannot be used after unary '{1}' without parentheses"},
          {48, "TypeScript static blocks are not supported in JavaScript"},
          {109, "event attributes must be camelCase: '{1}'"},
          {183, "missing body for finally clause"},
          {278, "unicode byte order mark (BOM) cannot appear before #! at beginning of script"},
          {111, "expected ')' to close function call"},
          {14, "'await' is only allowed in async functions"},
          {153, "interface properties are always public and cannot be marked {0}"},
          {0, ""},
          {135, "free {1} and {0} {1} {2}"},
          {49, "TypeScript type annotations are not allowed in JavaScript code"},
          {229, "object literal started here"},
          {146, "if statement needs parentheses around condition"},
          {154, "interfaces cannot contain static blocks"},
          {263, "unexpected 'default' outside switch statement"},
          {144, "hex number literal has no digits"},
          {0, ""},
          {292, "while loop needs parentheses around condition"},
          {238, "remove '{0}' to update an existing variable"},
          {0, ""},
          {0, ""},
          {206, "missing name or parentheses for function"},
          {27, "'{0}' operator cannot be used before '**' without parentheses"},
          {191, "missing comparison; '{1}' does not extend to the right side of '{0}'"},
          {71, "assignment-asserted fields are not supported in interfaces"},
          {254, "unclosed object literal; expected '}'"},
          {194, "missing condition for while statement"},
          {210, "missing parentheses around left-hand side of '**'"},
          {211, "missing parentheses around operand of '{0}'"},
          {260, "unexpected '\\' in identifier"},
          {45, "TypeScript interface properties cannot be private"},
          {85, "cannot reference private variables without object; use 'this.'"},
          {5, "\"globals\" descriptor must be a boolean or an object"},
          {261, "unexpected 'case' outside switch statement"},
          {282, "unopened block comment"},
          {257, "unclosed template"},
          {62, "another invalid string, do not use outside benchmark"},
          {58, "a function statement is not allowed as the body of {1:singular}"},
          {81, "cannot export variable named 'let'"},
          {269, "unexpected characters in octal literal"},
          {6, "\"globals\" must be an object"},
          {264, "unexpected 'finally' without 'try'"},
          {190, "missing comma between object literal entries"},
          {288, "variable declared here"},
          {299, "{1:headlinese} value must be a compile-time constant"},
          {29, "BigInt literal contains decimal point"},
          {0, ""},
          {0, ""},
          {0, ""},
          {177, "missing body for 'if' statement"},
          {167, "mismatched JSX tags; expected '</{1}>'"},
          {198, "missing function parameter list"},
          {252, "unclosed identifier escape sequence"},
          {0, ""},
          {277, "unexpected token in variable declaration; expected variable name"},
          {0, ""},
          {188, "missing catch or finally clause for try statement"},
          {110, "existing variable declared here"},
          {0, ""},
          {0, ""},
          {0, ""},
          {276, "unexpected token in export; expected 'export default ...' or 'export {{name}' or 'export * from ...' or 'export class' or 'export function' or 'export let'"},
          {287, "variable assigned before its declaration"},
          {0, ""},
          {0, ""},
          {0, ""},
          {197, "missing for loop header"},
          {0, ""},
          {272, "unexpected identifier in expression; missing operator before"},
          {168, "missing ',' between variable declarations"},
          {258, "unexpected '#'"},
          {139, "function starts here"},
          {0, ""},
          {69, "assignment to imported variable"},
          {16, "'else' has no corresponding 'if'"},
          {0, ""},
          {293, "with statement is missing '{1}' around expression"},
          {70, "assignment to undeclared variable"},
          {0, ""},
          {3, "\"globals\" descriptor \"shadowable\" property must be a boolean"},
          {64, "arrow is here"},
          {0, ""},
          {0, ""},
          {118, "expected expression before newline"},
          {200, "missing initializer in const declaration"},
          {284, "use of undeclared type: {0}"},
          {142, "generator function '*' belongs before function name"},
          {0, ""},
          {204, "missing name of exported class"},
          {19, "'if' statement"},
          {73, "binary number literal has no digits"},
          {18, "'for' loop"},
          {220, "missing semicolon between init and condition parts of for loop"},
          {0, ""},
          {103, "do-while loop needs parentheses around condition"},
          {0, ""},
          {0, ""},
          {266, "unexpected characters in binary literal"},
          {0, ""},
          {104, "do-while statement starts here"},
          {201, "missing name for class method"},
          {176, "missing body for 'for' loop"},
          {147, "imported variable declared here"},
          {300, "~~~ invalid string, do not use outside benchmark ~~~"},
          {112, "expected ',' between object literal entries"},
          {182, "missing body for do-while loop"},
          {249, "unclosed block comment"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {115, "expected 'from' before module specifier"},
          {0, ""},
          {256, "unclosed string literal"},
          {63, "array started here"},
          {132, "for-in loop expression cannot have semicolons"},
          {137, "function called before declaration in block scope: {0}"},
          {225, "new variable shadows existing variable"},
          {250, "unclosed class; expected '}' by end of file"},
          {119, "expected expression before semicolon"},
          {164, "let statement cannot declare variables named 'let'"},
          {230, "octal literal may not have decimal"},
          {281, "unmatched parenthesis"},
          {297, "{0} is not allowed in JavaScript"},
          {247, "this {1} looks fishy"},
          {36, "TypeScript 'implements' is not allowed in JavaScript"},
          {0, ""},
          {102, "do-while loop is missing '{1}' around condition"},
          {178, "missing body for 'switch' statement"},
          {96, "computed value disables enum autoincrement"},
          {166, "methods should not use the 'function' keyword"},
          {0, ""},
          {0, ""},
          {232, "octal number literal has no digits"},
          {0, ""},
          {0, ""},
          {0, ""},
          {255, "unclosed regexp literal"},
          {68, "assignment to const variable before its declaration"},
          {11, "'?' creates a conditional expression"},
          {279, "unmatched '}'"},
          {0, ""},
          {125, "expected {1:headlinese}"},
          {39, "TypeScript generics are not allowed in JavaScript code"},
          {13, "'await' cannot be followed by an arrow function; use 'async' instead"},
          {143, "here"},
          {268, "unexpected characters in number literal"},
          {160, "keywords cannot contain escape sequences"},
          {51, "TypeScript's 'interface' feature is not allowed in JavaScript code"},
          {0, ""},
          {270, "unexpected control character"},
          {271, "unexpected expression; missing key for object entry"},
          {222, "missing variable name"},
          {298, "{0} with no bindings"},
          {0, ""},
          {189, "missing catch variable name between parentheses"},
          {0, ""},
          {0, ""},
          {289, "variable used before declaration: {0}"},
          {0, ""},
          {0, ""},
          {21, "'readonly static' is not allowed; write 'static readonly' instead"},
          {145, "if statement is missing '{1}' around condition"},
          {0, ""},
          {72, "attribute has wrong capitalization; write '{1}' instead"},
          {0, ""},
          {95, "commas are not allowed between class methods"},
          {24, "'{0}' found here"},
          {17, "'extends' must be before 'implements'"},
          {82, "cannot export variable named keyword '{0}'"},
          {26, "'{0}' is not allowed on methods"},
          {97, "computer enum member name must be a simple string"},
          {0, ""},
          {86, "cannot update variable with '{0}' while declaring it"},
          {158, "invalid hex escape sequence: {0}"},
          {127, "exporting requires 'default'"},
          {140, "functions/methods should not have '=>'"},
          {236, "redeclaration of variable: {0}"},
          {0, ""},
          {181, "missing body for class"},
          {0, ""},
          {174, "missing 'while (condition)' for do-while statement"},
          {195, "missing end of array; expected ']'"},
          {265, "unexpected '{0}'"},
          {223, "misspelled React attribute; write '{1}' instead"},
          {214, "missing property name between '.' and '.'"},
          {173, "missing 'if' after 'else'"},
          {131, "for loop needs an iterable, or condition and update clauses"},
          {0, ""},
          {0, ""},
          {0, ""},
          {57, "a class statement is not allowed as the body of {1:singular}"},
          {114, "expected 'from \"name_of_module.mjs\"'"},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {0, ""},
          {94, "commas are not allowed after spread parameter"},
          {227, "number literal contains consecutive underscores"},
          {0, ""},
          {155, "invalid UTF-8 sequence"},
          {0, ""},
          {0, ""},
          {0, ""},
          {224, "move the 'extends' clause before 'implements' here"},
          {0, ""},
          {248, "try statement starts here"},
          {0, ""},
          {0, ""},
          {286, "variable already declared here"},
          {163, "legacy octal literals may not contain underscores"},
          {134, "forwarding exports are only allowed in export-from"},
          {0, ""},
          {0, ""},
          {0, ""},
          {121, "expected parameter for arrow function, but got a literal instead"},
          {193, "missing condition for switch statement"},
          {37, "TypeScript assignment-asserted fields are not supported in JavaScript"},
          {47, "TypeScript optional properties are not allowed in JavaScript code"},
          {66, "assignment to const global variable"},
  };
  // clang-format on

  std::uint64_t hash = hash_fnv_1a_64(untranslated, 14695981039346658397ULL);
  std::uint64_t table_size = 451;
  for (std::uint64_t attempt = 0; attempt <= 4; ++attempt) {
    const const_hash_entry& hash_entry =
        const_hash_table[(hash + attempt * attempt) % table_size];
    if (hash_entry.mapping_table_index == 0) {
      break;
    }
    if (hash_entry.untranslated == untranslated) {
      return hash_entry.mapping_table_index;
    }
  }

  // If you see an error with the following line, translation-table-generated.h
  // is out of date. Run tools/update-translator-sources to rebuild this file.
  QLJS_CONSTEXPR_ASSERT(false);

  return 0;
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
