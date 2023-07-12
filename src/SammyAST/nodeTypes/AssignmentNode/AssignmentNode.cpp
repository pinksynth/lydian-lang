#include "./AssignmentNode.h"

#pragma once

namespace sammylang {

void AssignmentNode::pushToExpressionList(Node *node) { child = node; };
void AssignmentNode::popCurrentExpressionList() { child = nullptr; };

std::vector<Node *> AssignmentNode::getCurrentExpressionList(ScopeType _scope) {
  std::vector<Node *> *vec = new std::vector<Node *>();
  vec->push_back(child);
  return *vec;
};

std::string AssignmentNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "Assignment node: \"" + variable + "\" -> (\n";
  if (child == NULL) {
    output += padString + "  " + "null";
  } else {
    output += child->inspectString(pad + 1);
  }
  output += "\n" + padString + ")";

  return output;
}

json AssignmentNode::toJson() {
  json nodeJson = {{"nodeType", "nt_assignment"},
                   {"variable", variable},
                   {"child", (child == NULL ? nullptr : child->toJson())}};

  return nodeJson;
};

} // namespace sammylang
