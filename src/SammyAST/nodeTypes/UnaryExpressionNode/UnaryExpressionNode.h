#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

#pragma once

namespace sammylang {

class UnaryExpressionNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(ScopeType scope, Node *node);
  void popCurrentExpressionList();
  std::string inspectString(int pad = 0);
  json toJson();

  std::string op;

  Node *child;

  UnaryExpressionNode() { nodeType = nt_unaryExpression; };
};

} // namespace sammylang
