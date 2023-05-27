#include "../NodeType.cpp"

#pragma once
class Node {

public:
  Node *parent;
  NodeType nodeType;

  virtual void pushToExpressionList(Node *node);
  virtual std::string inspectString(int pad = 0);
};