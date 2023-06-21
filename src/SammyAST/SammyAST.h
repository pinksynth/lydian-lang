#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "./Node.h"
#include <vector>

#pragma once

namespace sammylang {

class SammyAST {

public:
  json jsonAST;
  void fromTokens(std::vector<Token> tokens);

private:
  std::vector<Node *> currentExpressionList;

  Node *node;

  Token token;
  TokenType tokenType;
  Token nextToken;
  TokenType nextTokenType;
  Token thirdToken;
  TokenType thirdTokenType;

  // FIXME: This should not be static and should just use a scopes instance variable.
  static void pop_scopes(std::vector<ScopeType> *scopes);
  static Node *getTerminalNodeFromToken(Token token);

  void handleBinaryOperator();
};

} // namespace sammylang