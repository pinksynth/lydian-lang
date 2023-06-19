#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

namespace sammylang {

class NilNode : public Node {
public:
  std::string inspectString(int pad = 0);
  json toJson();

  NilNode() { nodeType = nt_nil; }
};

} // namespace sammylang
