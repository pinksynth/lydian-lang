#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class NodeBoolean : public Node {
public:
  std::string inspectString(int pad = 0);
  std::string value;
  bool booleanValue;

  NodeBoolean(Token token) {
    nodeType = nt_identifier;
    value = token.value;
    booleanValue = value == "true";
  }
};