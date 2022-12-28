#include "../Lexer.h"

void Lexer::handleIncrementLinesAndColumns() {
  if (character == '\n') {
    currentLineNumber++;
    currentColumnNumber = 1;
    currentLineValue = "";
  } else {
    currentColumnNumber++;
    // currentLineValue += character
  };
};
