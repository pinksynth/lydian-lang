#include <vector>

#include "../../../NodeType.cpp"
#include "../../Node.h"

#pragma once

namespace sammylang {

class FunctionCallNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);
  json toJson();

  Node *callee;
  std::vector<Node *> arguments;

  FunctionCallNode() {
    nodeType = nt_functionCall;
    arguments = {};
  };
};

} // namespace sammylang
