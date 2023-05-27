#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class NodeIdentifier : public Node {
public:
  std::string inspectString(int pad = 0);
  std::string value;

  NodeIdentifier(Token token) {
    nodeType = nt_identifier;
    value = token.value;
  }
};