#include <unistd.h>
#include <vector>

#include "../NodeType.cpp"
#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./Node.cpp"
#include "./SammyAST.h"

// Node types
#include "./nodeTypes/BooleanNode/BooleanNode.cpp"
#include "./nodeTypes/ConciseLambdaArgNode/ConciseLambdaArgNode.cpp"
#include "./nodeTypes/IdentifierNode/IdentifierNode.cpp"
#include "./nodeTypes/ListNode/ListNode.cpp"
#include "./nodeTypes/NilNode/NilNode.cpp"
#include "./nodeTypes/NumberNode/NumberNode.cpp"
#include "./nodeTypes/RootNode/RootNode.cpp"

// Handlers
#include "./handlers/handleBinaryOperator.cpp"
#include "./handlers/handleVariableAssignment.cpp"

#pragma once

namespace sammylang {

void SammyAST::fromTokens(std::vector<Token> unfilteredTokens) {
  std::vector<Token> tokens;

  std::copy_if(unfilteredTokens.begin(), unfilteredTokens.end(), std::back_inserter(tokens),
               [](Token token) { return token.type != tt_whitespace && token.type != tt_comment; });

  root = new RootNode();
  node = root;
  scopes = {st_root};
  debug("Inside SammyAST...");

  size_t tokensCount = tokens.size();
  for (i = 0; i < tokensCount; i++) {
    debug("\n\n==================================================\n");
    ScopeType currentScope = scopes.back();
    currentExpressionList = node->getCurrentExpressionList(currentScope);
    token = tokens[i];
    tokenType = token.type;

    debug("Token: " + token.value + "\n");

    debug("Current AST JSON: " + root->toJson().dump() + "\n");
    debug("Current AST: " + root->inspectString());

    if (node != NULL) {
      debug("Current Node:");
      debug(nodeString(node->nodeType) + "\n");
      //   jsonAST = node->toJson();
      //   debug(jsonAST.dump() + "\n");
    }

    debugScopes(scopes);

    // Ignore all whitespace. This language only uses whitespace at the lexer level, not the AST level.
    if (tokenType == tt_whitespace)
      continue;

    if (i < tokensCount - 1) {
      nextToken = tokens[i + 1];
    } else {
      nextToken = Token();
    }
    nextTokenType = nextToken.type;

    if (i < tokensCount - 2) {
      thirdToken = tokens[i + 2];
    } else {
      thirdToken = Token();
    }
    thirdTokenType = thirdToken.type;
    debug(token.inspectString());
    debug("Token type: " + std::to_string(tokenType));
    // debug("nextToken");
    // debug(nextToken.inspectString());
    // debug("nextTokenType");
    // debug(nextTokenType);
    // debug("thirdToken");
    // debug(thirdToken.inspectString());
    // debug("thirdTokenType");
    // debug(thirdTokenType);

    // Variable assignment
    if (tokenType == tt_var && nextTokenType == tt_assignment) {

      handleVariableAssignment();
      continue;
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

    debug("currentExpressionList.size()");
    debug(currentExpressionList.size());
    // debug("inspect(currentExpressionList)");
    // debug(inspect(currentExpressionList));

    if (inList(tokenType, tt_BINARY_OPERATORS) && currentExpressionList.size() > 0) {
      handleBinaryOperator();
      continue;
    }

    if (isTerminal(tokenType)) {
      // Get node from token and push onto children.
      Node *child = getTerminalNodeFromToken(token);
      child->parent = node;
      debug("Pushing to expression list...");
      node->pushToExpressionList(child);

      if (inList(currentScope, st_operandScopeTypes))
        pop_scopes();

      continue;
    }
  }

  if (node != NULL) {
    debug("FINAL AST:");
    debug(root->inspectString());

    jsonAST = root->toJson();
    debug("FINAL AST JSON:");
    debug(jsonAST.dump(2));
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

void SammyAST::consumeExtra() { i++; };

} // namespace sammylang