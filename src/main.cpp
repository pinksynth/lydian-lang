#include <fstream>
#include <iostream>
#include <string>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./LydianAST/LydianAST.cpp"

int main() {
  // FIXME: Figure out why this path works correctly with the CMake tools but not with your "Debug Language" command.
  // std::string testInput =
  //     lydianlang::getFileString("../../tests/cases/operator-precedence-small-1/input.lydian");
  std::string testInput = R"lydian(2 + 3 * 4 + 5)lydian";
  lydianlang::print("Test input:");
  lydianlang::print(testInput);

  lydianlang::debug("Compiling...");
  lydianlang::Lexer lexer = lydianlang::Lexer();
  std::vector<lydianlang::Token> tokens = lexer.lex(testInput);
  lydianlang::LydianAST ast = lydianlang::LydianAST();
  ast.fromTokens(tokens);

  std::ofstream("debug_tokens.json") << lexer.jsonTokens.dump(2);
  std::ofstream("debug_ast.json") << ast.jsonAST.dump(2);

  return 0;
};
