#include <unistd.h>
#include <vector>

#include "../NodeType.cpp"
#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./Node.cpp"
#include "./SammyAST.h"
#include "./handlers/handleBinaryOperator.cpp"
#include "./nodeTypes/BooleanNode/BooleanNode.cpp"
#include "./nodeTypes/ConciseLambdaArgNode/ConciseLambdaArgNode.cpp"
#include "./nodeTypes/IdentifierNode/IdentifierNode.cpp"
#include "./nodeTypes/ListNode/ListNode.cpp"
#include "./nodeTypes/NilNode/NilNode.cpp"
#include "./nodeTypes/NumberNode/NumberNode.cpp"
#include "./nodeTypes/RootNode/RootNode.cpp"

#pragma once

namespace sammylang {

void SammyAST::fromTokens(std::vector<Token> tokens) {
  RootNode *root = new RootNode();
  node = root;
  scopes = {st_root};
  debug("Inside SammyAST...");

  size_t tokensCount = tokens.size();
  for (size_t i = 0; i < tokensCount; i++) {
    // sleep(1);
    debug("\n\n==================================================\n");
    ScopeType currentScope = scopes.back();
    currentExpressionList = node->getCurrentExpressionList(currentScope);
    token = tokens[i];
    tokenType = token.type;

    debug("Token: " + token.value);

    if (node != NULL) {
      debug("Latest JSON:");
      jsonAST = node->toJson();
      debug(jsonAST.dump());
    }

    debugScopes(scopes);

    // Ignore all whitespace. This language only uses whitespace at the lexer level, not the AST level.
    if (tokenType == tt_whitespace)
      continue;

    if (i != tokensCount - 1) {
      nextToken = tokens[i + 1];
      nextTokenType = nextToken.type;
    }

    if (i != tokensCount - 2) {
      thirdToken = tokens[i + 2];
      thirdTokenType = thirdToken.type;
    }

    if (tokenType == tt_bracketOpen) {
      ListNode *listNode = new ListNode();
      Node *child = listNode;
      child->parent = node;
      node->pushToExpressionList(child);
      scopes.push_back(st_array);
      node = child;

      continue;
    }

    if (tokenType == tt_bracketClose) {
      pop_scopes();

      continue;
    }

    if (inList(tokenType, tt_BINARY_OPERATORS) && currentExpressionList.size() > 0) {
      handleBinaryOperator();
      continue;
    }

    if (isTerminal(tokenType) && !isBinaryOperator(nextTokenType)) {
      // Get node from token and push onto children.
      Node *child = getTerminalNodeFromToken(token);
      child->parent = node;
      node->pushToExpressionList(child);

      if (inList(currentScope, st_operandScopeTypes))
        pop_scopes();

      continue;
    }
  }

  if (node != NULL) {
    debug("AST:");
    debug(root->inspectString());

    jsonAST = root->toJson();
    debug("JSON:");
    debug(jsonAST.dump());
  }
};

Node *SammyAST::getTerminalNodeFromToken(Token token) {
  switch (token.type) {
  case tt_var:
    return new IdentifierNode(token);

  case tt_number:
    return new NumberNode(token);

  case tt_boolean:
    return new BooleanNode(token);

  case tt_nil:
    return new NilNode();

  case tt_conciseLambdaArgument:
    return new ConciseLambdaArgNode(token);

  default:
    // throw std::out_of_range("Encountered an unknown token type.");
    // break;
    return new Node();
  }
};

void SammyAST::pop_scopes() {
  if (scopes.size() > 0)
    scopes.pop_back();

  ScopeType currentScope = scopes.back();

  node = node->parent;

  if (inList(currentScope, st_operandScopeTypes))
    pop_scopes();
}

} // namespace sammylang