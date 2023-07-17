#include "./GenericExpressionNode.h"

#pragma once

namespace lydianlang {

void GenericExpressionNode::pushToExpressionList(ScopeType _scope, Node *node) {
  if (child == nullptr) {
    child = node;
  } else {
    throw std::logic_error("Only one child expression is allowed in a generic expression. E.g., (a "
                           "* b) is allowed, but (a b) is not.");
  }
};
void GenericExpressionNode::popCurrentExpressionList() { child = nullptr; };

std::vector<Node *> GenericExpressionNode::getCurrentExpressionList(ScopeType _scope) {
  std::vector<Node *> *vec = new std::vector<Node *>();
  vec->push_back(child);
  return *vec;
};

llvm::Value *GenericExpressionNode::codegen() { return child->codegen(); };

std::string GenericExpressionNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "Generic Expression Node: (\n";

  if (child == NULL)
    output += padString + "  " + "null";
  else
    output += child->inspectString(pad + 1);

  output += "\n" + padString + ")";

  return output;
}

json GenericExpressionNode::toJson() {
  json nodeJson = {{"nodeType", "nt_genericExpression"},
                   {"child", (child == NULL ? nullptr : child->toJson())}};

  return nodeJson;
};

} // namespace lydianlang
