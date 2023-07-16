#include "./NilNode.h"

namespace lydianlang {

std::string NilNode::inspectString(int pad) { return "Nil Node"; };

json NilNode::toJson() {
  json nilJson = {{"nodeType", "nt_nil"}};
  return nilJson;
};

} // namespace lydianlang
