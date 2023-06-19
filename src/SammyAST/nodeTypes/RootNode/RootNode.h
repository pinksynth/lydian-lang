#include "../../../NodeType.cpp"
#include "../../Node.h"
#include <vector>

class RootNode : public Node {
public:
  std::vector<Node *> children;
  std::vector<Node *> getCurrentExpressionList(ScopeType scope);
  void pushToExpressionList(Node *node);
  std::string inspectString(int pad = 0);
  json toJson();

  RootNode() {
    nodeType = nt_root;
    children = {};
  }
};