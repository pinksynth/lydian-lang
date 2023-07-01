#include "./BinaryExpressionNode.h"

#pragma once

namespace sammylang {

std::vector<Node *> BinaryExpressionNode::getCurrentExpressionList(ScopeType scope) {
  return children;
}

void BinaryExpressionNode::pushToExpressionList(Node *node) { right = node; };

std::string BinaryExpressionNode::inspectString(int pad) {
  std::string padString = "";
  for (int i = 0; i <= pad; i++) {
    padString += " ";
  }
  std::string output = "Binary Expression Node: [\n" + left->inspectString(pad + 2) + padString +
                       op + " \n" + right->inspectString(pad + 2);

  output += padString + "]";
  return output;
};

json BinaryExpressionNode::toJson() {
  json nodeJson = {{"nodeType", nt_list},
                   {"left", (left == NULL ? nullptr : left->toJson())},
                   {"right", (right == NULL ? nullptr : right->toJson())},
                   {"operator", op}};

  return nodeJson;
};

} // namespace sammylang
