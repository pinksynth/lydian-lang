#include <iostream>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./SammyAST/SammyAST.cpp"

std::string testInput = R"sammy(a 2)sammy";

int main() {
  debug("Compiling...");
  Lexer lexer = Lexer();
  std::vector<Token> tokens = lexer.lex(testInput);
  SammyAST ast = SammyAST();
  ast.fromTokens(tokens);

  return 0;
};
