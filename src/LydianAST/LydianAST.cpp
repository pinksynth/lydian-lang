#include <unistd.h>
#include <vector>

#include "../llvmSetup.h"

#include "../NodeType.cpp"
#include "../ScopeType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./LydianAST.h"
#include "./Node.cpp"

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
#include "./handlers/handleCloseCurly.cpp"
#include "./handlers/handleCloseParen.cpp"
#include "./handlers/handleFunctionCall.cpp"
#include "./handlers/handleFunctionDefinitionName.cpp"
#include "./handlers/handleGenericExpressionOpen.cpp"
#include "./handlers/handleUnaryOperator.cpp"
#include "./handlers/handleVariableAssignment.cpp"

// Other AST Helpers
#include "./prepareCallableLeftSibling.cpp"

#pragma once

namespace lydianlang {

void LydianAST::fromTokens(std::vector<Token> unfilteredTokens) {
  std::vector<Token> tokens;

  std::copy_if(unfilteredTokens.begin(), unfilteredTokens.end(), std::back_inserter(tokens),
               [](Token token) { return token.type != tt_whitespace && token.type != tt_comment; });

  root = new RootNode();
  node = root;
  scopes = {st_root};

  size_t tokensCount = tokens.size();
  for (i = 0; i < tokensCount; i++) {
    highlightDebug("\n\n==================================================\n");
    currentScope = scopes.back();
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

    auto [callableLeftSibling, appendedScopes] = prepareCallableLeftSibling(currentExpressionList);

    // Variable assignment
    if (tokenType == tt_var && nextTokenType == tt_assignment) {
      handleVariableAssignment();

      continue;
    }

    // Opening of function definition
    if (tokenType == tt_function) {
      if (nextTokenType != tt_var)
        throw std::logic_error("The fn keyword must be followed by an identifier.");

      if (thirdTokenType != tt_parenOpen)
        throw std::logic_error("Unexpected token after function identifier.");

      handleFunctionDefinitionName();

      continue;
    }

    if (currentScope == st_functionDecArgs && tokenType == tt_parenClose) {
      if (nextTokenType != tt_curlyOpen)
        throw std::logic_error(
            "Unexpected token after function declaration arguments. Expected \"{\"");

      swapScope(st_functionDecBody);
      consumeExtra();

      continue;
    }

    // Function call, if we saw an open paren and the left sibling is callable
    if (tokenType == tt_parenOpen && callableLeftSibling != nullptr) {
      handleFunctionCall(callableLeftSibling, appendedScopes);

      continue;
    }

    if (tokenType == tt_parenOpen) {
      handleGenericExpressionOpen();

      continue;
    }

    if (tokenType == tt_bracketOpen) {
      ListNode *listNode = new ListNode();
      Node *child = listNode;
      child->parent = node;
      node->pushToExpressionList(currentScope, child);
      scopes.push_back(st_array);
      node = child;

      continue;
    }

    if (tokenType == tt_parenClose) {
      handleCloseParen(currentScope);
      continue;
    }

    if (tokenType == tt_bracketClose) {
      popScopes();

      continue;
    }

    if (tokenType == tt_curlyClose) {
      handleCloseCurly();

      continue;
    }

    debug("currentExpressionList.size()");
    debug(currentExpressionList.size());
    // debug("inspect(currentExpressionList)");
    // debug(inspect(currentExpressionList));

    if (inList(tokenType, tt_BINARY_OPERATORS) && currentExpressionList.size() > 0 &&
        currentExpressionList.back() != nullptr) {
      handleBinaryOperator();

      continue;
    }

    // Unary operators, such as ! or -
    if (inList(tokenType, tt_UNARY_OPERATORS)) {
      handleUnaryOperator();

      continue;
    }

    // if (tt.UNARY_OPERATORS.includes(tokenType)) {
    //   handleUnaryOperator(context)
    //   continue
    // }

    if (isTerminal(tokenType)) {
      // Get node from token and push onto children.
      Node *child = getTerminalNodeFromToken(token);
      child->parent = node;
      // debug("Pushing to expression list...");
      node->pushToExpressionList(currentScope, child);

      if (inList(currentScope, st_operandScopeTypes))
        popScopes();

      continue;
    }
  }

  debug("FINAL AST:");
  debug(root->inspectString());

  jsonAST = root->toJson();
  debug("FINAL AST JSON:");
  debug(jsonAST.dump(2));

  setupLLVM();

  auto *ir = root->codegen();
  debug("FINAL LLVM IR:");
  ir->print(llvm::errs());
};

Node *LydianAST::getTerminalNodeFromToken(Token token) {
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

void LydianAST::swapScope(ScopeType scope) {
  scopes.pop_back();
  scopes.push_back(scope);
};

void LydianAST::popScopes() {
  if (scopes.size() > 0)
    scopes.pop_back();

  ScopeType currentScope = scopes.back();

  if (node->parent == nullptr) {
    throw std::logic_error("Parent of node " + nodeString(node->nodeType) + " is null.");
  }
  node = node->parent;

  if (inList(currentScope, st_operandScopeTypes))
    popScopes();
}

void LydianAST::consumeExtra() { i++; };

} // namespace lydianlang