#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

class RootNode : public Node {
public:
  std::vector<Node *> children;
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);

  RootNode() {
    nodeType = nt_root;
    children = {};
  }
};