#include "./ListNode.h"

#pragma once

std::vector<Node *> ListNode::getCurrentExpressionList(ScopeType scope) { return children; };

void ListNode::pushToExpressionList(Node *node) { children.push_back(node); };

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
    childJson.push_back(child->toJson());
  }

  json nodeJson = {{"nodeType", nt_list}, {"children", childJson}};

  return nodeJson;
};