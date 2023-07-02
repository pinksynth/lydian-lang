#include "./NumberNode.h"

namespace sammylang {

std::string NumberNode::inspectString(int pad) {
  return "Number Node: " + value + " (" + std::to_string(doubleValue) + ")";
};

json NumberNode::toJson() {
  json numberJson = {{"nodeType", "nt_literalNumber"}, {"value", doubleValue}};
  return numberJson;
};

} // namespace sammylang
