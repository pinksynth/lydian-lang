#include <vector>

#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "./Node.h"
#include "./nodeTypes/RootNode/RootNode.h"

#pragma once

namespace sammylang {

class SammyAST {

public:
  json jsonAST;
  void fromTokens(std::vector<Token> tokens);

private:
  std::vector<Node *> currentExpressionList;
  std::vector<ScopeType> scopes;

  size_t i;

  RootNode *root;
  Node *node;

  Token token;
  TokenType tokenType;
  Token nextToken;
  TokenType nextTokenType;
  Token thirdToken;
  TokenType thirdTokenType;

  void pop_scopes();
  static Node *getTerminalNodeFromToken(Token token);

  void consumeExtra();

  void handleBinaryOperator();
  void handleVariableAssignment();
};

} // namespace sammylang