#include "../CharacterType.cpp"
#include "../InterpolationContextStack/InterpolationContextStack.h"
#include "../Token.cpp"
#include <iostream>
#include <vector>

#pragma once
class Lexer {
  // These values change while in the loop to consume characters.
  char character;
  char nextCharacter;
  char thirdCharacter;
  CharacterType charType;
  CharacterType nextCharacterType;
  CharacterType thirdCharacterType;

  // These values are state that persists as the loop consumes characters.
  std::string charAccumulator = "";
  int currentColumnNumber = 1;
  int currentLineNumber = 1;
  std::string currentLineValue = "";
  std::string input;
  bool lambdaArgIdentifierMode = false;
  CharacterType latestCharacterType;
  bool multilineCommentMode = false;
  bool numberFloatingPointApplied = false;
  bool numberMode = false;
  bool singleLineCommentMode = false;
  bool stringLiteralMode = false;
  int tokenColumnNumberStart = 1;
  int tokenLineNumberStart = 1;
  // tokens: [],
  InterpolationContextStack ics;

  void defineLatestCharType();
  void resetState();
  Token *getToken();
  bool shouldContinueConsumingToken();

  // Handlers (in order)
  void handleCloseLambdaArgIdentifierMode();
  void handleOpenLambdaArgIdentifierMode();
  void handleTokenStartNumber();
  void handleRangeOperator();
  void handlePeriodWhileInNumberMode();
  void handleEndNumberMode();
  void handleStrings();
  void handleOpenStringInterpolation();
  void handleOpenSingleLineComment();
  void handleCloseSingleLineComment();
  void handleOpenMultilineComment();
  void handleCloseMultilineComment();
  void handleIncrementLinesAndColumns();

  // Debugging
  void printCharInfo(char character);

public:
  void lex(std::string input);

  // Debugging (public)
  void inspect();
};
