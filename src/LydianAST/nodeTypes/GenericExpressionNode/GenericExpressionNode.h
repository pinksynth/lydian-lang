#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

#pragma once

namespace lydianlang {

class GenericExpressionNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(ScopeType scope, Node *node);
  void popCurrentExpressionList();
  std::string inspectString(int pad = 0);
  json toJson();

  Node *child;

  GenericExpressionNode() { nodeType = nt_genericExpression; };
};

} // namespace lydianlang
