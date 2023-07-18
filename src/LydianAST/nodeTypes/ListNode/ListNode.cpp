#include "./ListNode.h"
#include "../../../utils.cpp"

#pragma once

namespace lydianlang {

std::vector<Node *> ListNode::getCurrentExpressionList(ScopeType scope) { return children; };

void ListNode::pushToExpressionList(ScopeType scope, Node *node) { children.push_back(node); };
void ListNode::popCurrentExpressionList(ScopeType _scope) { children.pop_back(); };

llvm::Value *ListNode::codegen() {
  throw std::logic_error("The method for LLVM codegen is not yet implemented for ListNode.");
};

std::string ListNode::inspectString(int pad) {
  std::string output = "List Node: [\n";
  std::string padString = getPadString(pad);

  for (Node *node : children) {
    output += padString + node->inspectString(pad + 1) + "\n";
  }
  output += padString + "]";
  return output;
};

json ListNode::toJson() {
  json childJson;

  for (Node *child : children)
    childJson.push_back(child->toJson());

  json nodeJson = {{"nodeType", "nt_list"}, {"children", childJson}};

  return nodeJson;
};

} // namespace lydianlang
