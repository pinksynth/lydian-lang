#include "../../../NodeType.cpp"
#include "../../../Token.cpp"
#include "../../Node.h"
#include <vector>

class NodeConciseLambdaArg : public Node {
public:
  std::string inspectString(int pad = 0);
  std::string value;
  int id;

  NodeConciseLambdaArg(Token token) {
    nodeType = nt_conciseLambdaArgument;
    value = token.value;
    id = std::stoi(value.substr(1));
  }
};