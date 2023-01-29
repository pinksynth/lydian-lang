// FIXME: These imports are probably unhygienic. I should really find somebody who uses this language and ask them.
#include "../src/utils.cpp"

#include "../src/InterpolationContextStack/InterpolationContextStack.cpp"
#include "../src/Lexer/Lexer.cpp"
#include "../src/Token.cpp"
#include "../src/TokenType.cpp"
#include "./testUtils.cpp"

#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

std::ifstream f("../tests/tmpTestFile.json");
json data = json::parse(f);

TEST_CASE("Placeholder for comparing tokens") {
  std::string testInput = R"sammy(
a = 1 + 2
)sammy";

  Lexer lexer = Lexer();
  std::vector<Token> expected = {
      Token("\n", tt_whitespace, 1, 1, 2, 1), Token("a", tt_var, 2, 1, 2, 2),
      Token(" ", tt_whitespace, 2, 2, 2, 3),  Token("=", tt_assignment, 2, 3, 2, 4),
      Token(" ", tt_whitespace, 2, 4, 2, 5),  Token("1", tt_number, 2, 5, 2, 6),
      Token(" ", tt_whitespace, 2, 6, 2, 7),  Token("+", tt_operatorInfix, 2, 7, 2, 8),
      Token(" ", tt_whitespace, 2, 8, 2, 9),  Token("2", tt_number, 2, 9, 2, 10)};
  std::vector<Token> received = lexer.lex(testInput);

  compareTokens(expected, received);
}
