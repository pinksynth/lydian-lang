#include "./Lexer/Lexer.cpp"
#include <iostream>

std::string testInput = "a = 1 + 2";

int main() {
  std::cout << "Compiling..." << std::endl;
  Lexer lexer = Lexer();
  lexer.lex(testInput);

  return 0;
};
