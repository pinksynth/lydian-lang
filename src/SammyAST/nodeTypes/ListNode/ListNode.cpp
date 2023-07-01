#include "./ListNode.h"
#include "../../../utils.cpp"

#pragma once

namespace sammylang {

std::vector<Node *> ListNode::getCurrentExpressionList(ScopeType scope) { return children; };

void ListNode::pushToExpressionList(Node *node) { children.push_back(node); };
void ListNode::popCurrentExpressionList() { children.pop_back(); };

std::string ListNode::inspectString(int pad) {
  std::string output = "List Node: [\n";

  std::string padString = "";
  for (int i = 0; i <= pad; i++) {
    padString += " ";
  }

  for (Node *node : children) {
    output += padString + node->inspectString(pad + 2) + "\n";
  }
  output += padString + "]";
  return output;
};

json ListNode::toJson() {
  json childJson;

  for (Node *child : children) {
    if (child == NULL)
      debug("Child is null for some reason...");
    else
      childJson.push_back(child->toJson());
  }

  json nodeJson = {{"nodeType", nt_list}, {"children", childJson}};

  return nodeJson;
};

} // namespace sammylang
