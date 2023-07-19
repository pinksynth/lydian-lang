#include "../nodeTypes/IfExpressionNode/IfExpressionNode.cpp"

#pragma once

namespace lydianlang {

void LydianAST::handleKeywordIf() {
  scopes.push_back(st_ifCondition);

  IfExpressionNode *ifExpressionNode = new IfExpressionNode();
  ifExpressionNode->parent = node;
  node->pushToExpressionList(currentScope, ifExpressionNode);
  node = ifExpressionNode;
};

} // namespace lydianlang
