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
  virtual void popCurrentExpressionList();
  virtual std::string inspectString(int pad = 0);
  virtual json toJson();
};

} // namespace lydianlang
