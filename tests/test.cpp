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
#include <sstream>
#include <vector>

#include "./cases/booleans-1/test.cpp"

TEST_CASE("Lexer produces desired token output") {
  // std::ifstream file("../tests/tmpTestFile.json");
  // json data = json::parse(file);
  // std::vector<Token> expectedTokens = tokenArrayFromJson(data);

  // std::ifstream inputFileStream("../tests/tmpTestFile.sammy");
  // std::ostringstream inputFileStreamString;
  // inputFileStreamString << inputFileStream.rdbuf();
  // std::string inputString = inputFileStreamString.str();

  // Lexer lexer = Lexer();
  // std::vector<Token> received = lexer.lex(inputString);

  // compareTokens(expectedTokens, received);
}
