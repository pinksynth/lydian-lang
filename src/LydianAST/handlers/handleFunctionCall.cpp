#include "../nodeTypes/FunctionCallNode/FunctionCallNode.cpp"

#pragma once

namespace lydianlang {

void LydianAST::handleFunctionCall(Node *callableLeftSibling,
                                   std::vector<ScopeType> appendedScopes) {
  // Note that if callableLeftSibling involved drilling into any binary expressions or assignments, those have been appended.
  for (ScopeType scope : appendedScopes)
    scopes.push_back(scope);

  ScopeType prevScope = scopes.back();

  // Remove the callable left sibling from its parent and set that parent as the node
  node = callableLeftSibling->parent;

  currentExpressionList = node->getCurrentExpressionList(prevScope);
  currentExpressionList.pop_back();
  node->popCurrentExpressionList();

  scopes.push_back(st_functionCallArgs);

  FunctionCallNode *functionCallNode = new FunctionCallNode();
  functionCallNode->callee = callableLeftSibling;
  node->pushToExpressionList(st_functionCallArgs, functionCallNode);
  functionCallNode->parent = node;

  // Once the function call node has replaced the callable lefthand sibling node, set the current node to the function call node so we can proceed to consume arguments.
  node = functionCallNode;
};

} // namespace lydianlang