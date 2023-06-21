#include "./SammyAST.h"
#include "../NodeType.cpp"
#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./Node.cpp"
#include "./handlers/handleBinaryOperator.cpp"
#include "./nodeTypes/BooleanNode/BooleanNode.cpp"
#include "./nodeTypes/ConciseLambdaArgNode/ConciseLambdaArgNode.cpp"
#include "./nodeTypes/IdentifierNode/IdentifierNode.cpp"
#include "./nodeTypes/ListNode/ListNode.cpp"
#include "./nodeTypes/NilNode/NilNode.cpp"
#include "./nodeTypes/NumberNode/NumberNode.cpp"
#include "./nodeTypes/RootNode/RootNode.cpp"
#include <vector>

#pragma once

namespace sammylang {

void SammyAST::fromTokens(std::vector<Token> tokens) {
  RootNode root = RootNode();
  node = &root;
  std::vector<ScopeType> scopes = {st_root};

  size_t tokensCount = tokens.size();
  for (size_t i = 0; i < tokensCount; i++) {
    ScopeType currentScope = scopes.back();
    currentExpressionList = node->getCurrentExpressionList(currentScope);
    token = tokens[i];
    tokenType = token.type;

    debugScopes(scopes);

    debug("Token: " + token.value);

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
      Node *child = new ListNode();
      child->parent = node;
      debug("Abouts to add");
      node->pushToExpressionList(child);
      debug("Abouts to push");
      scopes.push_back(st_array);
      debug("Pushed");
      node = child;

      continue;
    }
    if (tokenType == tt_bracketClose) {
      pop_scopes(&scopes);
      node = node->parent;

      continue;
    }
    if (isTerminal(tokenType) && !isBinaryOperator(nextTokenType)) {
      // Get node from token and push onto children.
      Node *child = getTerminalNodeFromToken(token);
      child->parent = node;
      node->pushToExpressionList(child);

      if (inList(currentScope, st_operandScopeTypes))
        pop_scopes(&scopes);

      continue;
    }

    debug(token.inspectString());
  }

  debug("AST:");
  debug(node->inspectString());

  jsonAST = node->toJson();
  debug("JSON:");
  debug(jsonAST.dump());
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

void SammyAST::pop_scopes(std::vector<ScopeType> *scopes) {
  if (scopes->size() > 0)
    scopes->pop_back();
}

} // namespace sammylang