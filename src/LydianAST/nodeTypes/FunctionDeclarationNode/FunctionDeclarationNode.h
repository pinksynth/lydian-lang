#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

namespace lydianlang {

class FunctionDeclarationNode : public Node {
public:
  std::string name;
  std::vector<Node *> children;
  std::vector<Node *> arguments;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList(ScopeType scope) override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  FunctionDeclarationNode() { nodeType = nt_functionDeclaration; }

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
