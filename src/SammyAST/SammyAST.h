#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "./Node.h"
#include <vector>

#pragma once

namespace sammylang {

class SammyAST {
  static void pop_scopes(std::vector<ScopeType> *scopes);
  static Node *getTerminalNodeFromToken(Token token);

public:
  json jsonAST;
  void fromTokens(std::vector<Token> tokens);
};

} // namespace sammylang