#include "./Lexer.h"
#include <iostream>

void Lexer::lex(std::string input) {
  std::cout << "Inside lexer." << std::endl;
  std::cout << input << std::endl;

  // TODO: We will not have UTF8 support until we change this. "input.length" is
  // just bytes.
  int max = input.length();
  for (size_t index = 0; index < max; index++) {
    char character = input[index];
    char nextCharacter = input[index + 1];
    char thirdCharacter = input[index + 1];

    std::cout << "======================" << std::endl;
    std::cout << "Character: " << character << std::endl;
  }
};
