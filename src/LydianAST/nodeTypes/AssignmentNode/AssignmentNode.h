#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

#pragma once

namespace lydianlang {

class AssignmentNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList() override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  std::string variable;
  Node *child;
  bool weak = false;

  AssignmentNode() { nodeType = nt_assignment; };

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
