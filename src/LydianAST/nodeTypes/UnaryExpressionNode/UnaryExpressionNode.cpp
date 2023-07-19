#include "./UnaryExpressionNode.h"

#pragma once

namespace lydianlang {

void UnaryExpressionNode::pushToExpressionList(ScopeType _scope, Node *node) {
  if (child == nullptr) {
    child = node;
  } else {
    throw std::logic_error("Only one child expression is allowed in a unary expression.");
  }
};
void UnaryExpressionNode::popCurrentExpressionList(ScopeType _scope) { child = nullptr; };

std::vector<Node *> UnaryExpressionNode::getCurrentExpressionList(ScopeType _scope) {
  std::vector<Node *> *vec = new std::vector<Node *>();
  vec->push_back(child);
  return *vec;
};

llvm::Value *UnaryExpressionNode::codegen() {
  throw std::logic_error(
      "The method for LLVM codegen is not yet implemented for UnaryExpressionNode.");
};

std::string UnaryExpressionNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "Unary Expression Node: (\n";

  output += padString + "  OP: " + op + "\n";

  if (child == NULL)
    output += padString + "  " + "null";
  else
    output += child->inspectString(pad + 1);

  output += "\n" + padString + ")";

  return output;
}

json UnaryExpressionNode::toJson() {
  json nodeJson = {{"nodeType", "nt_unaryExpression"},
                   {"child", (child == NULL ? nullptr : child->toJson())}};

  return nodeJson;
};

} // namespace lydianlang
