#include "./RootNode.h"

void RootNode::pushToExpressionList(Node *node) { children.push_back(node); };

std::string RootNode::inspectString(int pad) {
  std::string output = "Root Node: [\n";

  std::string padString = "";
  for (int i = 0; i <= pad; i++) {
    padString += " ";
  }

  for (Node *node : children) {
    output += padString + node->inspectString(pad + 2) + "\n";
  }
  output += "]";
  return output;
};

json RootNode::toJson() {
  json childJson = json::array();
  for (Node *child : children) {
    childJson.push_back(child->toJson());
  }

  json nodeJson = {{"nodeType", nt_root}, {"children", childJson}};

  return nodeJson;
};