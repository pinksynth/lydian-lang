#include "../NodeType.cpp"
#include "../ScopeType.cpp"

#pragma once

namespace lydianlang {

class Node {

public:
  Node *parent;
  NodeType nodeType;

  virtual std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  virtual void pushToExpressionList(ScopeType scope, Node *node);
  virtual void popCurrentExpressionList(ScopeType scope);
  virtual std::string inspectString(int pad = 0);
  virtual json toJson();

  // LLVM
  // Node that for Lydian this is not a pure virtual method because we must be able to instantiate a Node pointer.
  virtual llvm::Value *codegen(); // = 0;
};

} // namespace lydianlang
