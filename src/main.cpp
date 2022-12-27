#include "./Lexer/Lexer.cpp"
#include <iostream>

int main() {
  std::cout << "Hello world!" << std::endl;
  Lexer lexer = Lexer();
  lexer.lex();

  return 0;
};
