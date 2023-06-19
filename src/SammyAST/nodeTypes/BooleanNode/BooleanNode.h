#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

namespace sammylang {

class BooleanNode : public Node {
public:
  std::string inspectString(int pad = 0);
  json toJson();
  std::string value;
  bool booleanValue;

  BooleanNode(Token token) {
    nodeType = nt_literalBoolean;
    value = token.value;
    booleanValue = value == "true";
  }
};

} // namespace sammylang
