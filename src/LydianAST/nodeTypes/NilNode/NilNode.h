#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

namespace lydianlang {

class NilNode : public Node {
public:
  std::string inspectString(int pad = 0) override;
  json toJson() override;

  NilNode() { nodeType = nt_nil; }

  // LLVM
  llvm::Value *codegen() override;
};

} // namespace lydianlang
