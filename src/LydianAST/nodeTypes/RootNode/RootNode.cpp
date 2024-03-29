#include "./RootNode.h"

#pragma once

namespace lydianlang {

std::vector<Node *> RootNode::getCurrentExpressionList(ScopeType scope) { return children; };

void RootNode::pushToExpressionList(ScopeType scope, Node *node) { children.push_back(node); };
void RootNode::popCurrentExpressionList(ScopeType _scope) { children.pop_back(); };

llvm::Value *RootNode::codegen() {
  // Until I figure out how to do blocks, just codegen the last item in the children list.
  return children.back()->codegen();
};

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

} // namespace lydianlang
