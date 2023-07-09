#include <fstream>
#include <iostream>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./SammyAST/SammyAST.cpp"

int main() {
  // FIXME: Figure out why this path works correctly with the CMake tools but not with your "Debug Language" command.
  // std::string testInput =
  //     sammylang::getFileString("../../tests/cases/operator-precedence-small-1/input.sammy");
  std::string testInput = R"sammy(
    # These ones work for operator precedence:
    # 4 * 5 + 6 * 7
    # a + b - c * d + e / f

    # This one doesn't.
    a = 4 * 5 + 6 * 7 - 1 - b + 6 / 9 -> foo
  )sammy";
  sammylang::print("Test input:");
  sammylang::print(testInput);

  sammylang::debug("Compiling...");
  sammylang::Lexer lexer = sammylang::Lexer();
  std::vector<sammylang::Token> tokens = lexer.lex(testInput);
  sammylang::SammyAST ast = sammylang::SammyAST();
  ast.fromTokens(tokens);

  return 0;
};
