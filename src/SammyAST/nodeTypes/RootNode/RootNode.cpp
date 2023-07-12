#include "./RootNode.h"

#pragma once

namespace sammylang {

std::vector<Node *> RootNode::getCurrentExpressionList(ScopeType scope) { return children; };

void RootNode::pushToExpressionList(Node *node) { children.push_back(node); };
void RootNode::popCurrentExpressionList() { children.pop_back(); };

std::string RootNode::inspectString(int pad) {
  std::string output = "Root Node: [\n";
  std::string padString = getPadString(pad);

  for (Node *node : children) {
    if (node != nullptr) {
      output += padString + node->inspectString(pad + 1) + "\n";
    }
  }
  output += padString + "]";
  return output;
};

json RootNode::toJson() {
  json childJson = json::array();
  for (Node *child : children) {
    childJson.push_back(child->toJson());
  }

  json nodeJson = {{"nodeType", "nt_root"}, {"children", childJson}};

  return nodeJson;
};

} // namespace sammylang
