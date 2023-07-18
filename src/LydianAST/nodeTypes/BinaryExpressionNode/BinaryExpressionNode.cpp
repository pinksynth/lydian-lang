#include "./BinaryExpressionNode.h"

#pragma once

namespace lydianlang {

std::vector<Node *> BinaryExpressionNode::getCurrentExpressionList(ScopeType _scope) {
  return children;
}

void BinaryExpressionNode::pushToExpressionList(ScopeType scope, Node *node) { right = node; };
void BinaryExpressionNode::popCurrentExpressionList(ScopeType _scope) { right = nullptr; };

llvm::Value *BinaryExpressionNode::codegen() {
  llvm::Value *l = left->codegen();
  llvm::Value *r = right->codegen();

  if (!l || !r)
    return nullptr;

  if (op == "+")
    return Builder->CreateFAdd(l, r, "addtmp");

  if (op == "-")
    return Builder->CreateFSub(l, r, "subtmp");

  if (op == "*")
    return Builder->CreateFMul(l, r, "multmp");

  if (op == "/")
    return Builder->CreateFDiv(l, r, "multmp");

  if (op == "<") {
    l = Builder->CreateFCmpULT(l, r, "cmptmp");
    // Convert bool 0/1 to double 0.0 or 1.0
    return Builder->CreateUIToFP(l, llvm::Type::getDoubleTy(*TheContext), "booltmp");
  }

  if (op == ">") {
    l = Builder->CreateFCmpUGT(l, r, "cmptmp");
    // Convert bool 0/1 to double 0.0 or 1.0
    return Builder->CreateUIToFP(l, llvm::Type::getDoubleTy(*TheContext), "booltmp");
  }

  throw std::logic_error("Binary operator does not yet support LLVM codegen: " + op);
};

std::string BinaryExpressionNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "Binary Expression Node: [\n";
  output += padString + "  LEFT:\n";
  output += (left == nullptr ? padString + "  null" : left->inspectString(pad + 1)) + "\n";
  output += padString + "  OP: " + op + "\n";
  output += padString + "  RIGHT:\n";
  output += (right == nullptr ? padString + "  null" : right->inspectString(pad + 1)) + "\n";
  output += "\n" + padString + "]";
  return output;
};

json BinaryExpressionNode::toJson() {
  json nodeJson = {{"nodeType", "nt_binaryExpression"},
                   {"left", (left == nullptr ? nullptr : left->toJson())},
                   {"right", (right == nullptr ? nullptr : right->toJson())},
                   {"operator", op}};

  return nodeJson;
};

} // namespace lydianlang
