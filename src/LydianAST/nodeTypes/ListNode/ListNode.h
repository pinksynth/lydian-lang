#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

namespace lydianlang {

class ListNode : public Node {
public:
  std::vector<Node *> children;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope) override;
  void pushToExpressionList(ScopeType scope, Node *node) override;
  void popCurrentExpressionList() override;
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  ListNode() { nodeType = nt_list; }

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
