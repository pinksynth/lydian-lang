#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

#pragma once

namespace lydianlang {

class UnaryExpressionNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList() override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  std::string op;

  Node *child;

  UnaryExpressionNode() { nodeType = nt_unaryExpression; };

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
