#include "../src/TokenType.cpp"

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

std::vector<Token> tokenArrayFromJson(json jsonArray) {
  std::vector<Token> tokens = {};

  for (json::iterator item = jsonArray.begin(); item != jsonArray.end(); ++item)
    tokens.push_back(Token(*item));

  return tokens;
};

void compareTokens(std::vector<Token> expectedTokens, std::vector<Token> receivedTokens) {
  unsigned expectedTokensIndex = 0;
  unsigned receivedTokensIndex = 0;
  unsigned expectedSize = expectedTokens.size();
  unsigned receivedSize = receivedTokens.size();

  while (expectedTokensIndex < expectedSize || receivedTokensIndex < receivedSize) {
    Token tokenA = expectedTokens[expectedTokensIndex];
    Token tokenB = receivedTokens[receivedTokensIndex];

    REQUIRE(tokenA == tokenB);

    if (expectedTokensIndex < expectedSize)
      ++expectedTokensIndex;

    if (receivedTokensIndex < receivedSize)
      ++receivedTokensIndex;

    if ((expectedTokensIndex == expectedSize && receivedTokensIndex < receivedSize)) {
      throw std::logic_error("Lexer produced too many tokens.");
    } else if (receivedTokensIndex == receivedSize && expectedTokensIndex < expectedSize) {
      throw std::logic_error("Lexer produced too few tokens.");
    }
  }
}
