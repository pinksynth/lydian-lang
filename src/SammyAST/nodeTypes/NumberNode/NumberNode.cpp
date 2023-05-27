#include "./NumberNode.h"

std::string NumberNode::inspectString(int pad) {
  return "Number Node: " + value + " (" + std::to_string(doubleValue) + ")";
};
