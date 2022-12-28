#include "./Lexer.h"
#include "../CharacterType.cpp"
#include "../InterpolationContextStack/InterpolationContextStack.h"
#include "../charTypeFrom.cpp"
#include <format>
#include <iostream>

#pragma once
void Lexer::lex(std::string input) {
  print("Lexer received input:\n" + input);

  resetState();

  inspect();

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

    printCharInfo(character);
  }
};

void Lexer::printCharInfo(char character) {
  print("======================");
  std::string message = "Character: ";
  if (character == '\n')
    message += "(newline)";
  else
    message += character;

  print(message);
};

void Lexer::resetState() {
  charAccumulator = "abc";
  currentColumnNumber = 1;
  currentLineNumber = 1;
  currentLineValue = "";
  // input;
  lambdaArgIdentifierMode = false;
  multilineCommentMode = false;
  numberFloatingPointApplied = false;
  numberMode = false;
  singleLineCommentMode = false;
  stringLiteralMode = false;
  tokenColumnNumberStart = 1;
  tokenLineNumberStart = 1;
  // tokens: [],
  ics = InterpolationContextStack();
};

void Lexer::inspect() {
  std::string output = "Lexer state {\n";

  PRINT_MEMBER(charAccumulator);
  output += "  " + PRINT_MEMBER(charAccumulator) + "\n";
  output += "  " + PRINT_MEMBER(currentLineValue) + "\n";
  output += "  ICS: " + ics.inspectString() + "\n";
  output += "  Modes\n";
  output += "    " + PRINT_MEMBER(lambdaArgIdentifierMode) + "\n";
  output += "    " + PRINT_MEMBER(multilineCommentMode) + "\n";
  output += "    " + PRINT_MEMBER(numberMode) + "\n";
  output += "    " + PRINT_MEMBER(singleLineCommentMode) + "\n";
  output += "    " + PRINT_MEMBER(stringLiteralMode) + "\n";
  output += "    " + PRINT_MEMBER(numberFloatingPointApplied) + "\n";
  output += "  Char meta\n";
  output += "    " + PRINT_MEMBER(tokenColumnNumberStart) + "\n";
  output += "    " + PRINT_MEMBER(tokenLineNumberStart) + "\n";
  output += "    " + PRINT_MEMBER(currentColumnNumber) + "\n";
  output += "    " + PRINT_MEMBER(currentLineNumber) + "\n";
  // input
  // tokens

  output += "}\n";
  print(output);
};
