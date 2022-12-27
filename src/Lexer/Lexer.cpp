#include "./Lexer.h"
#include <iostream>

#pragma once
#include "../CharacterType.cpp"
#include "../charTypeFrom.cpp"

void Lexer::lex(std::string input) {
  std::cout << "Lexer received input." << std::endl << input << std::endl;

  // TODO: We will not have UTF8 support until we change this. "input.length" is just bytes.
  int max = input.length();
  for (size_t index = 0; index < max; index++) {
    char character = input[index];
    char nextCharacter = input[index + 1];
    char thirdCharacter = input[index + 1];
    CharacterType charType = charTypeFrom(character);

    std::cout << "======================" << std::endl;
    std::cout << "Character: " << character << " " << charType << std::endl;
  }
};
