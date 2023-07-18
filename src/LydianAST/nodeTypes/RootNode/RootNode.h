#include <vector>

#include "../../../NodeType.cpp"
#include "../../Node.h"

#pragma once

namespace lydianlang {

class RootNode : public Node {
public:
  std::vector<Node *> children;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList(ScopeType scope) override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  RootNode() {
    nodeType = nt_root;
    children = {};
  }

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
