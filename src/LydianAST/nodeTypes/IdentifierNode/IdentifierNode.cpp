#include "./IdentifierNode.h"

namespace lydianlang {

llvm::Value *IdentifierNode::codegen() {
  throw std::logic_error("The method for LLVM codegen is not yet implemented for IdentifierNode.");
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
