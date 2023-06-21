#include "./Lexer.h"
#include "../CharacterType.cpp"
#include "../InterpolationContextStack/InterpolationContextStack.h"
#include "../TokenType.cpp"
#include "../charTypeFrom.cpp"
#include "./getToken.cpp"
#include "./handlers/handleCloseLambdaArgIdentifierMode.cpp"
#include "./handlers/handleCloseMultilineComment.cpp"
#include "./handlers/handleCloseSingleLineComment.cpp"
#include "./handlers/handleEndNumberMode.cpp"
#include "./handlers/handleIncrementLinesAndColumns.cpp"
#include "./handlers/handleOpenLambdaArgIdentifierMode.cpp"
#include "./handlers/handleOpenMultilineComment.cpp"
#include "./handlers/handleOpenSingleLineComment.cpp"
#include "./handlers/handleOpenStringInterpolation.cpp"
#include "./handlers/handlePeriodWhileInNumberMode.cpp"
#include "./handlers/handleRangeOperator.cpp"
#include "./handlers/handleStrings.cpp"
#include "./handlers/handleTokenStartNumber.cpp"
#include <format>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#pragma once

namespace sammylang {

std::vector<Token> Lexer::lex(std::string rawInput) {
  // debug("Lexer received input:\n" + rawInput);

  resetState();
  input = rawInput;

  inspect();

  json j;

  // TODO: We will not have UTF8 support until we change this. "input.length" is just bytes.
  int max = input.length();
  for (size_t tokenIndex = 0; tokenIndex < max; tokenIndex++) {
    index = tokenIndex;
    character = input[index];
    characterType = charTypeFrom(character);

    if (index > 0) {
      previousCharacter = input[index - 1];
      previousCharacterType = charTypeFrom(previousCharacter);
    } else {
      previousCharacterType = ct_NONE;
    }

    if (index < max - 1) {
      nextCharacter = input[index + 1];
      nextCharacterType = charTypeFrom(nextCharacter);
    } else {
      nextCharacterType = ct_NONE;
    }

    if (index < max - 2) {
      thirdCharacter = input[index + 2];
      thirdCharacterType = charTypeFrom(thirdCharacter);
    } else {
      thirdCharacterType = ct_NONE;
    }

    defineLatestCharType();

    Token *token = getToken();
    if (token != NULL) {
      // debug(token->inspectString());
      j.push_back(token->toJson());
      pushToken(*token);
    } else {
      // debug("Token is null. Continuing...");
    }
    delete token;

    handleCloseLambdaArgIdentifierMode();
    handleOpenLambdaArgIdentifierMode();
    handleTokenStartNumber();
    handleRangeOperator();
    handlePeriodWhileInNumberMode();
    handleEndNumberMode();
    handleStrings();
    handleOpenStringInterpolation();
    handleOpenSingleLineComment();
    handleCloseSingleLineComment();
    handleOpenMultilineComment();
    handleCloseMultilineComment();
    handleIncrementLinesAndColumns();

    charAccumulator += character;

    printCharInfo(character);
    inspect();
  }

  inspect();

  // We have stopped consuming tokens, so reset any types for remaining characters. Unsure if these values are actually what we want, but they seem to work.
  character = 0;
  nextCharacter = 0;
  thirdCharacter = 0;
  characterType = ct_NONE;
  nextCharacterType = ct_NONE;
  thirdCharacterType = ct_NONE;

  defineLatestCharType();

  Token *token = getToken();
  if (token != NULL) {
    // debug(token->inspectString());
    j.push_back(token->toJson());
    pushToken(*token);
  } else {
    // debug(charAccumulator);
  }

  // debug(j.dump(2));

  return tokens;
};

void Lexer::pushToken(Token token) {
  tokens.push_back(token);
  tokenLineNumberStart = currentLineNumber;
  tokenColumnNumberStart = currentColumnNumber;
  charAccumulator = {};
};

void Lexer::resetState() {
  charAccumulator = "";
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

void Lexer::defineLatestCharType() {
  if (charAccumulator.length() > 0) {
    char character = charAccumulator[charAccumulator.length() - 1];
    latestCharacterType = charTypeFrom(character);
  }
};

// Debugging

void Lexer::printCharInfo(char character){
    // debug("======================");
    // debug("Character: " + charString(character));
};

void Lexer::inspect() {
  std::string output = "Lexer state {\n";

  output += "  " + PRINT_MEMBER(charAccumulator) + "\n";
  output += "  " + PRINT_MEMBER(currentLineValue) + "\n";
  output += "  " + PRINT_MEMBER(latestCharacterType) + "\n";
  output += "  " + padded_label(60, "ICS", ics.inspectString()) + "\n";
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
  output += "  Tokens\n";
  output += inspectTokensString();
  output += "\n";
  // input
  // tokens

  output += "}\n";
  // debug(output);
};

std::string Lexer::inspectTokensString() {
  std::string output = "";
  for (Token token : tokens) {
    output += token.inspectString() + "; ";
  };
  return output;
};

} // namespace sammylang
