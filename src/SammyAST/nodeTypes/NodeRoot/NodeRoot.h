#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

class NodeRoot : public Node {
public:
  std::vector<Node *> children;
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);

  NodeRoot() {
    nodeType = nt_root;
    children = {};
  }
};