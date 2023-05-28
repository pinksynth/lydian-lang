#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

class ListNode : public Node {
public:
  std::vector<Node *> children;
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);
  json toJson();

  ListNode() {
    nodeType = nt_list;
    children = {};
  }
};