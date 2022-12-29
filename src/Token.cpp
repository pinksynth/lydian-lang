#include "./TokenType.cpp"
#include <iostream>

// NOTE: A struct might make more sense for this.
#pragma once
class Token {

public:
  TokenType type = tt_NONE;
  std::string value = "";

  // Meta
  int lineNumberStart;
  int columnNumberStart;
  int lineNumberEnd;
  int columnNumberEnd;

  std::string inspectString() {
    std::string message = "Token: ";
    message += value;
    return message;
  };
};
