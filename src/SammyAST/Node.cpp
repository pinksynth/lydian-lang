#include "./Node.h"

void Node::pushToExpressionList(Node node) {
  throw std::logic_error(
      "Cannot push a child to this node because its `pushToExpressionList` is not implemented.");
};

std::string Node::inspectString(int pad) {
  // throw std::logic_error("No implementation of 'inspectString' for the desired NodeType.");
  return "TODO: Create Terminal Node Classes";
};
