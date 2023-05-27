#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class NumberNode : public Node {
public:
  std::string inspectString(int pad = 0);
  std::string value;
  double doubleValue;

  NumberNode(Token token) {
    nodeType = nt_literalNumber;
    value = token.value;
    std::string underscoresStripped = value;
    replace_all(underscoresStripped, "_", "");
    doubleValue = std::stod(underscoresStripped);
  }
};