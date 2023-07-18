#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

#pragma once

namespace lydianlang {

class BinaryExpressionNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList(ScopeType scope) override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  Node *left;
  Node *right;
  std::string op;

  BinaryExpressionNode() { nodeType = nt_binaryExpression; };

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
