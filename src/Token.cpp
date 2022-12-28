#include "./TokenType.cpp"

// NOTE: A struct might make more sense for this.
#pragma once
class Token {

public:
  TokenType type;
  std::string value;

  // Meta
  int lineNumberStart;
  int columnNumberStart;
  int lineNumberEnd;
  int columnNumberEnd;
};
