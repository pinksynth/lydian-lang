#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class NodeNumber : public Node {
public:
  std::string inspectString(int pad = 0);
  std::string value;

  NodeNumber(Token token) {
    nodeType = nt_literalNumber;
    value = token.value;
  }
};