#include "./IdentifierNode.h"

namespace sammylang {

std::string IdentifierNode::inspectString(int pad) { return "Identifier Node: " + value; };

json IdentifierNode::toJson() {
  json identifierJson = {{"nodeType", "nt_identifier"}, {"value", value}};
  return identifierJson;
};

} // namespace sammylang
