#include "./BooleanNode.h"

namespace lydianlang {

llvm::Value *BooleanNode::codegen() {
  throw std::logic_error("The method for LLVM codegen is not yet implemented for BooleanNode.");
};

std::string BooleanNode::inspectString(int pad) {
  return "Boolean Node: " + value + " (" + std::to_string(booleanValue) + ")";
};

json BooleanNode::toJson() {
  json booleanJson = {{"nodeType", "nt_literalBoolean"}, {"value", booleanValue}};
  return booleanJson;
};

} // namespace lydianlang
