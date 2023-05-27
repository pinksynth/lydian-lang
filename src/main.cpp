#include <iostream>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./SammyAST/SammyAST.cpp"

std::string testInput = R"sammy(
  nil
  a
  2
  3.0
  4_000.5
  true
  false
  $1
  $25
)sammy";

int main() {
  debug("Compiling...");
  Lexer lexer = Lexer();
  std::vector<Token> tokens = lexer.lex(testInput);
  SammyAST ast = SammyAST();
  ast.fromTokens(tokens);

  return 0;
};
