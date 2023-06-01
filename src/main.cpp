#include <fstream>
#include <iostream>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./SammyAST/SammyAST.cpp"

int main() {
  std::string testInput = getFileString("../../tests/cases/lists-1/input.sammy");
  // std::string testInput = R"sammy(a [ b [ c d ] e ] f)sammy";
  std::cout << "Test input:" << std::endl;
  std::cout << testInput << std::endl;

  debug("Compiling...");
  Lexer lexer = Lexer();
  std::vector<Token> tokens = lexer.lex(testInput);
  SammyAST ast = SammyAST();
  ast.fromTokens(tokens);

  return 0;
};
