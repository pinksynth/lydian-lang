#include "./Node.h"

#pragma once

namespace sammylang {

void Node::pushToExpressionList(Node *node) {
  throw std::logic_error(
      "Cannot push a child to this node because its `pushToExpressionList` is not implemented.");
};

void Node::popCurrentExpressionList() { return; }

std::string Node::inspectString(int pad) {
  throw std::logic_error("No implementation of 'inspectString' for the desired NodeType.");
};

json Node::toJson() {
  throw std::logic_error("The method toJson is being called by a Node type for which it "
                         "is not implemented.");
};

std::vector<Node *> Node::getCurrentExpressionList(ScopeType scope) {
  throw std::logic_error("The method getCurrentExpressionList is being called by a Node type for "
                         "which it is not implemented.");
};

std::string inspect(std::vector<Node *> nodes, int pad = 0) {
  std::string output = "[\n";

  std::string padString = "";

  for (int i = 0; i <= pad; i++)
    padString += " ";

  for (Node *node : nodes)
    output += padString + node->inspectString(pad + 2) + "\n";

  output += padString + "]";
  return output;
};

} // namespace sammylang
