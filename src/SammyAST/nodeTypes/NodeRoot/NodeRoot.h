#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

class NodeRoot : public Node {
public:
  std::vector<Node> children;

  NodeRoot() {
    nodeType = nt_root;
    children = {};
  }
};