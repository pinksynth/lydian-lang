#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include <iostream>

std::string testInput = R"sammy(
a = 1 + 2
)sammy";

int main() {
  print("Compiling...");
  Lexer lexer = Lexer();
  lexer.lex(testInput);

  InterpolationContextStack ics = InterpolationContextStack();

  return 0;
};
