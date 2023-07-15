#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

namespace sammylang {

class FunctionDeclarationNode : public Node {
public:
  std::string name;
  std::vector<Node *> children;
  std::vector<Node *> arguments;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(ScopeType scope, Node *node);
  void popCurrentExpressionList();
  std::string inspectString(int pad = 0);
  json toJson();

  FunctionDeclarationNode() { nodeType = nt_functionDeclaration; }
};

} // namespace sammylang
