#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

namespace sammylang {

class ListNode : public Node {
public:
  std::vector<Node *> children;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);
  json toJson();

  ListNode() {
    nodeType = nt_list;
    children = {};
  }
};

} // namespace sammylang
