#include "./ListNode.h"

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
