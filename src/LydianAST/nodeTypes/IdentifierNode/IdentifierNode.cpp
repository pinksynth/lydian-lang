#include "./IdentifierNode.h"

namespace lydianlang {

std::string IdentifierNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  return padString + "Identifier Node: " + value;
};

json IdentifierNode::toJson() {
  json identifierJson = {{"nodeType", "nt_identifier"}, {"value", value}};
  return identifierJson;
};

} // namespace lydianlang
