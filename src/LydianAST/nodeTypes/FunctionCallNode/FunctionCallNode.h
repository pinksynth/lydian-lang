#include <vector>

#include "../../../NodeType.cpp"
#include "../../Node.h"

#pragma once

namespace lydianlang {

class FunctionCallNode : public Node {
  std::vector<Node *> children;

public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  Node *callee;
  std::vector<Node *> arguments;

  FunctionCallNode() {
    nodeType = nt_functionCall;
    arguments = {};
  };

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
