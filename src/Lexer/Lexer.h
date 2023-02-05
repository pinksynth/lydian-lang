#include "../CharacterType.cpp"
#include "../InterpolationContextStack/InterpolationContextStack.h"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <iostream>
#include <vector>

#pragma once

class Lexer {

  static std::unique_ptr<llvm::LLVMContext> TheContext;

  // These values change while in the loop to consume characters.
  int index;
  char previousCharacter;
  char character;
  char nextCharacter;
  char thirdCharacter;
  CharacterType previousCharacterType;
  CharacterType characterType;
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
  std::vector<Token> tokens = {};
  InterpolationContextStack ics;

  void defineLatestCharType();
  void resetState();
  Token *getToken();
  void pushToken(Token token);
  bool shouldContinueConsumingToken();
  TokenType getStringTokenType();

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
  std::string inspectTokensString();

public:
  std::vector<Token> lex(std::string input);

  // Debugging (public)
  void inspect();
};
