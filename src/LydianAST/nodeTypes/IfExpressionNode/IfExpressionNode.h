#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

namespace lydianlang {

class IfExpressionNode : public Node {
public:
  std::string name;
  std::vector<Node *> condition;
  std::vector<Node *> bodyChildren;
  std::vector<Node *> elseChildren;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList(ScopeType scope) override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  IfExpressionNode() { nodeType = nt_ifExpression; }

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
