#include "./NilNode.h"

namespace sammylang {

std::string NilNode::inspectString(int pad) { return "Nil Node"; };

json NilNode::toJson() {
  json nilJson = {{"nodeType", nt_nil}};
  return nilJson;
};

} // namespace sammylang
