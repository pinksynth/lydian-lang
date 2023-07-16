#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

namespace lydianlang {

class ConciseLambdaArgNode : public Node {
public:
  std::string inspectString(int pad = 0);
  json toJson();
  std::string value;
  int id;

  ConciseLambdaArgNode(Token token) {
    nodeType = nt_conciseLambdaArgument;
    value = token.value;
    id = std::stoi(value.substr(1));
  }
};

} // namespace lydianlang
