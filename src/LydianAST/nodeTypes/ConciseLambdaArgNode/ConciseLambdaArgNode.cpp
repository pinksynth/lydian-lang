#include "./ConciseLambdaArgNode.h"

namespace lydianlang {

llvm::Value *ConciseLambdaArgNode::codegen() {
  throw std::logic_error(
      "The method for LLVM codegen is not yet implemented for ConciseLambdaArgNode.");
};

std::string ConciseLambdaArgNode::inspectString(int pad) {
  return "Concise λ Arg Node: " + std::to_string(id);
};

json ConciseLambdaArgNode::toJson() {
  json lambdaJson = {{"nodeType", "nt_conciseLambdaArgument"}, {"id", id}};
  return lambdaJson;
};

} // namespace lydianlang
