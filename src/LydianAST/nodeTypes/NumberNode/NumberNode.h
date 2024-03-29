#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

namespace lydianlang {

class NumberNode : public Node {
public:
  std::string inspectString(int pad = 0) override;
  json toJson() override;
  std::string value;
  double doubleValue;

  NumberNode(Token token) {
    nodeType = nt_literalNumber;
    value = token.value;
    std::string underscoresStripped = value;
    replace_all(underscoresStripped, "_", "");
    doubleValue = std::stod(underscoresStripped);
  }

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
