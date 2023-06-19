#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

namespace sammylang {

class IdentifierNode : public Node {
public:
  std::string inspectString(int pad = 0);
  json toJson();
  std::string value;

  IdentifierNode(Token token) {
    nodeType = nt_identifier;
    value = token.value;
  }
};

} // namespace sammylang
