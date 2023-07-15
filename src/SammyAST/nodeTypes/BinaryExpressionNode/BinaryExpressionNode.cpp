#include "./BinaryExpressionNode.h"

#pragma once

namespace sammylang {

std::vector<Node *> BinaryExpressionNode::getCurrentExpressionList(ScopeType _scope) {
  return children;
}

void BinaryExpressionNode::pushToExpressionList(ScopeType scope, Node *node) { right = node; };
void BinaryExpressionNode::popCurrentExpressionList() { right = nullptr; };

std::string BinaryExpressionNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "Binary Expression Node: [\n" + padString + "  " + "LEFT:\n" +
                       (left == nullptr ? padString + "  null" : left->inspectString(pad + 1)) +
                       "\n" + padString + "  " + op + "\n" + padString + "  " + "RIGHT:\n" +
                       (right == nullptr ? padString + "  null" : right->inspectString(pad + 1));

  output += "\n" + padString + "]";
  return output;
};

json BinaryExpressionNode::toJson() {
  json nodeJson = {{"nodeType", "nt_binaryExpression"},
                   {"left", (left == nullptr ? nullptr : left->toJson())},
                   {"right", (right == nullptr ? nullptr : right->toJson())},
                   {"operator", op}};

  return nodeJson;
};

} // namespace sammylang
