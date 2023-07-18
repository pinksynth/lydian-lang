#include <vector>

#include "../llvmSetup.h"

#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "./Node.h"
#include "./nodeTypes/RootNode/RootNode.h"

#pragma once

namespace lydianlang {

class LydianAST {

public:
  json jsonAST;
  llvm::Value *ir;
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

  ScopeType currentScope = st_root;
  void popScopes();
  void swapScope(ScopeType scope);

  static Node *getTerminalNodeFromToken(Token token);

  void consumeExtra();

  void handleBinaryOperator();
  void handleCloseCurly();
  void handleCloseParen(ScopeType currentScope);
  void handleFunctionCall(Node *, std::vector<ScopeType>);
  void handleFunctionDefinitionName();
  void handleGenericExpressionOpen();
  void handleKeywordElse();
  void handleKeywordIf();
  void handleUnaryOperator();
  void handleVariableAssignment();
};

} // namespace lydianlang