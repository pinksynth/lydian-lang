#include <iostream>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"

std::string testInput = R"sammy(
a = 1 + 2
)sammy";

int main() {
  debug("Compiling...");
  Lexer lexer = Lexer();
  lexer.lex(testInput);

  return 0;
};
