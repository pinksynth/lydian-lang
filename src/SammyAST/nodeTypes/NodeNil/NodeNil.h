#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class NodeNil : public Node {
public:
  std::string inspectString(int pad = 0);

  NodeNil() { nodeType = nt_nil; }
};