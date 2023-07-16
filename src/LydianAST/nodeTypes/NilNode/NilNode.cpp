#include "./NilNode.h"

namespace lydianlang {

llvm::Value *NilNode::codegen() {
  throw std::logic_error("The method for LLVM codegen is not yet implemented for NilNode.");
};

std::string NilNode::inspectString(int pad) { return "Nil Node"; };

json NilNode::toJson() {
  json nilJson = {{"nodeType", "nt_nil"}};
  return nilJson;
};

} // namespace lydianlang
