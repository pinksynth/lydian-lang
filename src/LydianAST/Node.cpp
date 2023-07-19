#include "./Node.h"

#pragma once

namespace lydianlang {

void Node::pushToExpressionList(ScopeType scope, Node *node) {
  throw std::logic_error(
      "Cannot push a child to this node because its `pushToExpressionList` is not implemented.");
};

void Node::popCurrentExpressionList(ScopeType scope) { return; }

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

llvm::Value *Node::codegen() {
  throw std::logic_error("The method for LLVM codegen is being called on a Node type for which it "
                         "is not implemented.");
};

std::string inspect(std::vector<Node *> nodes, int pad = 0) {
  std::string padString = getPadString(pad);
  std::string output = padString + "[\n";

  for (Node *node : nodes) {
    if (node != nullptr) {
      output += node->inspectString(pad + 1) + "\n";
    }
  }

  output += padString + "]";
  return output;
};

std::string nodeString(Node *node) { return nodeString(node->nodeType); }

} // namespace lydianlang
