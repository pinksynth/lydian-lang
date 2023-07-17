#include "./IdentifierNode.h"

namespace lydianlang {

llvm::Value *IdentifierNode::codegen() {
  llvm::Value *llvmValue = NamedValues[value];

  if (!llvmValue)
    throw std::logic_error("Unknown variable name: " + value);

  return llvmValue;
};

std::string IdentifierNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  return padString + "Identifier Node: " + value;
};

json IdentifierNode::toJson() {
  json identifierJson = {{"nodeType", "nt_identifier"}, {"value", value}};
  return identifierJson;
};

} // namespace lydianlang
