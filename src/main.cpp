#include <fstream>
#include <iostream>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./SammyAST/SammyAST.cpp"

int main() {
  std::string testInput = sammylang::getFileString("../../tests/cases/assignment-1/input.sammy");
  // std::string testInput = R"sammy(a [ b [ c d ] e ] f)sammy";
  std::cout << "Test input:" << std::endl;
  std::cout << testInput << std::endl;

  sammylang::debug("Compiling...");
  sammylang::Lexer lexer = sammylang::Lexer();
  std::vector<sammylang::Token> tokens = lexer.lex(testInput);
  sammylang::SammyAST ast = sammylang::SammyAST();
  ast.fromTokens(tokens);

  return 0;
};
