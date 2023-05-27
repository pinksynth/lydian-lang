#include "../Token.cpp"
#include "./Node.h"
#include <vector>

#pragma once
class SammyAST {

public:
  void fromTokens(std::vector<Token> tokens);

  static Node *getTerminalNodeFromToken(Token token);
};
