#include "dtl/dtl.hpp"

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

// Makes assertions based on three files per test case. The test case's `input.sammy` is the Sammy Lang input. The Lexer produces tokens and those tokens are compared with `expectedTokens.json`. Then the tokens are fed to the AST, which is expected to look like `expectedAST.json`.
void doAssertions(std::filesystem::path currentFile) {
  std::ifstream inputFileStream(currentFile.parent_path() / "input.sammy");
  std::ostringstream inputFileStreamString;
  inputFileStreamString << inputFileStream.rdbuf();
  std::string inputString = inputFileStreamString.str();

  std::ifstream expectedTokensFileStream(currentFile.parent_path() / "expectedTokens.json");
  json expectedTokensJson = json::parse(expectedTokensFileStream);
  std::vector<Token> expectedTokens = tokenArrayFromJson(expectedTokensJson);

  Lexer lexer = Lexer();
  std::vector<Token> receivedTokens = lexer.lex(inputString);

  compareTokens(expectedTokens, receivedTokens);

  std::filesystem::path expectedASTPath(currentFile.parent_path() / "expectedAST.json");

  if (!std::filesystem::exists(expectedASTPath)) {
    alert("WARNING: Could not find " + expectedASTPath.generic_string());
  } else {
    std::ifstream expectedASTFileStream(expectedASTPath);
    json expectedASTJson = json::parse(expectedASTFileStream);

    SammyAST ast = SammyAST();
    ast.fromTokens(receivedTokens);
    json receivedASTJson = ast.jsonAST;
    REQUIRE(expectedASTJson == receivedASTJson);
  }
}
