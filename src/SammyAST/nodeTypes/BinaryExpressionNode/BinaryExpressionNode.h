#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

namespace sammylang {

class BinaryExpressionNode : public Node {
public:
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);
  json toJson();

  Node *left;
  Node *right;
  std::string op;

  BinaryExpressionNode() { nodeType = nt_binaryExpression; };
};

} // namespace sammylang
