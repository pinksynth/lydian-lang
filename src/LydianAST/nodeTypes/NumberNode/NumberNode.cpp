#include "./NumberNode.h"

namespace lydianlang {

llvm::Value *NumberNode::codegen() {
  return llvm::ConstantFP::get(*TheContext, llvm::APFloat(doubleValue));
};

std::string NumberNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  return padString + "Number Node: " + value + " (" + std::to_string(doubleValue) + ")";
};

json NumberNode::toJson() {
  json numberJson = {{"nodeType", "nt_literalNumber"}, {"value", doubleValue}};
  return numberJson;
};

} // namespace lydianlang
