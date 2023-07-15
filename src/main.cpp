#include <fstream>
#include <iostream>
#include <string>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./SammyAST/SammyAST.cpp"

int main() {
  // FIXME: Figure out why this path works correctly with the CMake tools but not with your "Debug Language" command.
  // std::string testInput =
  //     sammylang::getFileString("../../tests/cases/operator-precedence-small-1/input.sammy");
  std::string testInput = R"sammy(fn multiply(a) { a * a }
fn multiply(a b) { a * b }
)sammy";
  sammylang::print("Test input:");
  sammylang::print(testInput);

  sammylang::debug("Compiling...");
  sammylang::Lexer lexer = sammylang::Lexer();
  sammylang::debug("JSON Output from Lexer:");
  sammylang::debug(lexer.jsonTokens.dump(2));
  std::vector<sammylang::Token> tokens = lexer.lex(testInput);
  sammylang::SammyAST ast = sammylang::SammyAST();
  ast.fromTokens(tokens);
  sammylang::debug("JSON Output from AST:");
  sammylang::debug(ast.jsonAST.dump(2));

  std::ofstream("debug_tokens.json") << lexer.jsonTokens.dump(2);
  std::ofstream("debug_ast.json") << ast.jsonAST.dump(2);

  return 0;
};
