#include "./NodeRoot.h"

void NodeRoot::pushToExpressionList(Node node) { children.push_back(node); };

std::string NodeRoot::inspectString(int pad) {
  std::string output = "Root Node: [\n";
  for (Node node : children) {
    output += "  " + node.inspectString(pad + 2) + "\n";
  }
  output += "]";
  return output;
};
