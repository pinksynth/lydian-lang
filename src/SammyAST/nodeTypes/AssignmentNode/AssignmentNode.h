#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

#pragma once

namespace sammylang {

class AssignmentNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);
  json toJson();

  std::string variable;
  Node *child;
  bool weak = false;

  AssignmentNode() { nodeType = nt_assignment; };
};

} // namespace sammylang
