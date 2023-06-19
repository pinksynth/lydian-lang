#include "../NodeType.cpp"
#include "../ScopeType.cpp"

#pragma once

namespace sammylang {

class Node {

public:
  Node *parent;
  NodeType nodeType;

  virtual std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  virtual void pushToExpressionList(Node *node);
  virtual std::string inspectString(int pad = 0);
  virtual json toJson();
};

} // namespace sammylang
