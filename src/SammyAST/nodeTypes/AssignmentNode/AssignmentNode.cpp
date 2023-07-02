#include "./AssignmentNode.h"

#pragma once

namespace sammylang {

void AssignmentNode::pushToExpressionList(Node *node) { child = node; };

std::vector<Node *> AssignmentNode::getCurrentExpressionList(ScopeType scope) {
  std::vector<Node *> *vec = new std::vector<Node *>();
  vec->push_back(child);
  return *vec;
};

std::string AssignmentNode::inspectString(int pad) {
  std::string padString = "";
  for (int i = 0; i <= pad; i++) {
    padString += " ";
  }
  std::string output = "Assignment node: \"" + variable + "\" -> (";
  if (child == NULL) {
    output += "null";
  } else {
    output += child->inspectString(pad + 2);
  }
  output += ")";

  return output;
}

json AssignmentNode::toJson() {
  json nodeJson = {{"nodeType", "nt_assignment"},
                   {"variable", variable},
                   {"child", (child == NULL ? nullptr : child->toJson())}};

  return nodeJson;
};

} // namespace sammylang
