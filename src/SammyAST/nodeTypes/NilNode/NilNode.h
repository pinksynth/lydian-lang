#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class NilNode : public Node {
public:
  std::string inspectString(int pad = 0);
  json toJson();

  NilNode() { nodeType = nt_nil; }
};