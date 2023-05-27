#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class BooleanNode : public Node {
public:
  std::string inspectString(int pad = 0);
  std::string value;
  bool booleanValue;

  BooleanNode(Token token) {
    nodeType = nt_literalBoolean;
    value = token.value;
    booleanValue = value == "true";
  }
};