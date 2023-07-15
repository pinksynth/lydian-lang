#include "../nodeTypes/UnaryExpressionNode/UnaryExpressionNode.cpp"

#pragma once

namespace sammylang {

void SammyAST::handleUnaryOperator() {
  scopes.push_back(st_unaryOperator);
  UnaryExpressionNode *unaryExpressionNode = new UnaryExpressionNode();
  unaryExpressionNode->parent = node;
  unaryExpressionNode->op = token.value;
  node->pushToExpressionList(currentScope, unaryExpressionNode);
  node = unaryExpressionNode;
};

} // namespace sammylang
/*
const nt = require("./nodeTypes")
const st = require("./scopeTypes")

const handleUnaryOperator = ({
  node,
  pushToExpressionList,
  scopes,
  setNode,
  token,
}) => {
  scopes.push(st.UNARY_OPERATOR)

  const child = {
    operator: token.value,
    parent: node,
    type: nt.UNARY_EXPRESSION,
    lineNumberStart: token.lineNumberStart,
    columnNumberStart: token.columnNumberStart,
  }
  pushToExpressionList(child)
  setNode(child)
}

module.exports = handleUnaryOperator
*/