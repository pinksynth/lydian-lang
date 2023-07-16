#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

namespace lydianlang {

class IdentifierNode : public Node {
public:
  std::string inspectString(int pad = 0) override;
  json toJson() override;
  std::string value;

  IdentifierNode(Token token) {
    nodeType = nt_identifier;
    value = token.value;
  }

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
