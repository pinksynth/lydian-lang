#include <vector>

#include "../../../NodeType.cpp"
#include "../../Node.h"

#pragma once

namespace sammylang {

class RootNode : public Node {
public:
  std::vector<Node *> children;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(ScopeType scope, Node *node);
  void popCurrentExpressionList();
  std::string inspectString(int pad = 0);
  json toJson();

  RootNode() {
    nodeType = nt_root;
    children = {};
  }
};

} // namespace sammylang
