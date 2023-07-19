#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

#pragma once

namespace lydianlang {

class GenericExpressionNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList(ScopeType scope) override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  Node *child;

  GenericExpressionNode() { nodeType = nt_genericExpression; };

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
