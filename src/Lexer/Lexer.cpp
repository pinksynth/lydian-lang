#include "./Lexer.h"
#include <iostream>

#pragma once
#include "../CharacterType.cpp"
#include "../charTypeFrom.cpp"
#include "../utils.cpp"

void Lexer::lex(std::string input) {
  PRINT("Lexer received input:" << std::endl << input);

  // TODO: We will not have UTF8 support until we change this. "input.length" is just bytes.
  int max = input.length();
  for (size_t index = 0; index < max; index++) {
    char character = input[index];
    char nextCharacter;
    char thirdCharacter;
    CharacterType charType = charTypeFrom(character);
    CharacterType nextCharacterType;
    CharacterType thirdCharacterType;
    if (index < max - 1) {
      nextCharacter = input[index + 1];
      nextCharacterType = charTypeFrom(nextCharacter);
    }
    if (index < max - 2) {
      thirdCharacter = input[index + 2];
      thirdCharacterType = charTypeFrom(thirdCharacter);
    }

    PRINT("======================");
    PRINT("Character: " << character << " " << charType);
  }
};
