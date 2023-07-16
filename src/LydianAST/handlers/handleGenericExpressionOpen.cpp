#include "../nodeTypes/GenericExpressionNode/GenericExpressionNode.cpp"

#pragma once

namespace lydianlang {
void LydianAST::handleGenericExpressionOpen() {
  scopes.push_back(st_genericExpression);
  GenericExpressionNode *genericExpressionNode = new GenericExpressionNode();
  genericExpressionNode->parent = node;
  node->pushToExpressionList(currentScope, genericExpressionNode);
  node = genericExpressionNode;
};
} // namespace lydianlang

/*
const nt = require("./nodeTypes")
const st = require("./scopeTypes")

const handleGenericExpressionOpen = ({
  node,
  pushToExpressionList,
  scopes,
  setNode,
  token,
}) => {
  scopes.push(st.GENERIC_EXPRESSION)
  const child = {
    type: nt.GENERIC_EXPRESSION,
    parent: node,
    children: [],
    lineNumberStart: token.lineNumberStart,
    columnNumberStart: token.columnNumberStart,
  }

  pushToExpressionList(child)
  setNode(child)
}

module.exports = handleGenericExpressionOpen
*/