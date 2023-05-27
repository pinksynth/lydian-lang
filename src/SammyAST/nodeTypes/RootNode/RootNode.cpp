#include "./RootNode.h"

void RootNode::pushToExpressionList(Node *node) { children.push_back(node); };

std::string RootNode::inspectString(int pad) {
  std::string output = "Root Node: [\n";
  for (Node *node : children) {
    output += "  " + node->inspectString(pad + 2) + "\n";
  }
  output += "]";
  return output;
};
