#include <tuple>

#include "./Node.h"
#include "./nodeTypes/AssignmentNode/AssignmentNode.h"
#include "./nodeTypes/BinaryExpressionNode/BinaryExpressionNode.h"

#pragma once

// FIXME: Write test cases for this file. It should largely be proven by the "function call" and "big file" and "generic expression" cases, but it'd be better to have its internal behavior specified in a test.

namespace lydianlang {
std::tuple<Node *, std::vector<ScopeType>> getCallable(Node *leftSiblingExpression,
                                                       std::vector<ScopeType> appendedScopes = {}) {
  // Identifiers are callable.
  if (leftSiblingExpression->nodeType == nt_identifier) {
    return {leftSiblingExpression, appendedScopes};
  }

  // debug("leftSiblingExpression->inspectString()");
  // debug(leftSiblingExpression->inspectString());

  BinaryExpressionNode *leftSiblingBinaryExpression =
      dynamic_cast<BinaryExpressionNode *>(leftSiblingExpression);

  // Property access is considered callable.
  if (leftSiblingExpression->nodeType == nt_binaryExpression &&
      leftSiblingBinaryExpression->op == ".") {
    return {leftSiblingExpression, appendedScopes};
  }

  // For other binary expressions, keep recursing through the righthand side to see if we find a callable.
  Node *siblingDescendant = nullptr;
  ScopeType scopeType;
  if (leftSiblingExpression->nodeType == nt_binaryExpression) {
    siblingDescendant = leftSiblingBinaryExpression->right;
    scopeType = st_binaryOperator;
  } else if (leftSiblingExpression->nodeType == nt_assignment) {
    AssignmentNode *leftSiblingAssignment = dynamic_cast<AssignmentNode *>(leftSiblingExpression);
    siblingDescendant = leftSiblingAssignment->child;
    scopeType = st_assignment;
  }

  if (siblingDescendant != nullptr) {
    appendedScopes.push_back(scopeType);
    // debug("Calling getCallable");
    return getCallable(siblingDescendant, appendedScopes);
  } else {
    return {nullptr, {}};
  }
}

std::tuple<Node *, std::vector<ScopeType>>
prepareCallableLeftSibling(std::vector<Node *> currentExpressionList) {
  if (currentExpressionList.size() == 0)
    return {nullptr, {}};

  Node *leftSiblingExpression = currentExpressionList.back();

  if (leftSiblingExpression == nullptr)
    return {nullptr, {}};

  return getCallable(leftSiblingExpression);
}
} // namespace lydianlang
