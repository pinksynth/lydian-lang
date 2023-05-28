#include "./BooleanNode.h"

std::string BooleanNode::inspectString(int pad) {
  return "Boolean Node: " + value + " (" + std::to_string(booleanValue) + ")";
};

json BooleanNode::toJson() {
  json booleanJson = {{"nodeType", nt_literalBoolean}, {"value", booleanValue}};
  return booleanJson;
};