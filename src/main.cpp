#include "./Lexer/Lexer.cpp"
#include "./utils.cpp"
#include <iostream>

std::string testInput = R"sammy(
a = 1 + 2
)sammy";

int main() {
  PRINT("Compiling...");
  Lexer lexer = Lexer();
  lexer.lex(testInput);

  return 0;
};
