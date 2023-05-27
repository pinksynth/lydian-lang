#include "./BooleanNode.h"

std::string BooleanNode::inspectString(int pad) {
  return "Boolean Node: " + value + " (" + std::to_string(booleanValue) + ")";
};
