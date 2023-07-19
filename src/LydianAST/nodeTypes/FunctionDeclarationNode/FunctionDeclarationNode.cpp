#include "./FunctionDeclarationNode.h"
#include "../../../utils.cpp"

#pragma once

namespace lydianlang {

std::vector<Node *> FunctionDeclarationNode::getCurrentExpressionList(ScopeType scope) {

  return children;
};

void FunctionDeclarationNode::pushToExpressionList(ScopeType scope, Node *node) {
  if (scope == st_functionDecArgs) {
    arguments.push_back(node);

    return;
  }
  if (scope == st_functionDecBody) {
    children.push_back(node);

    return;
  }

  throw std::logic_error(
      "Invalid scope for `pushToExpressionList` on `FunctionDeclarationNode`. Must be ");
};

void FunctionDeclarationNode::popCurrentExpressionList(ScopeType _scope) { children.pop_back(); };

llvm::Value *FunctionDeclarationNode::codegen() {
  std::vector<llvm::Type *> argTypes(arguments.size(), llvm::Type::getDoubleTy(*TheContext));

  llvm::FunctionType *functionType =
      llvm::FunctionType::get(llvm::Type::getDoubleTy(*TheContext), argTypes, false);

  llvm::Function *llvmFunction =
      llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, name, TheModule.get());

  // Set names for all arguments.
  unsigned argIndex = 0;
  for (auto &llvmFunctionArg : llvmFunction->args()) {
    Node *argumentBaseNode = arguments[argIndex++];
    IdentifierNode *argumentIdentifierNode = dynamic_cast<IdentifierNode *>(argumentBaseNode);

    if (argumentIdentifierNode == nullptr)
      throw std::logic_error("Only identifier arguments are supported at this time. Found type: " +
                             nodeString(argumentBaseNode->nodeType));

    llvmFunctionArg.setName(argumentIdentifierNode->value);
  }

  llvm::BasicBlock *basicBlock =
      llvm::BasicBlock::Create(*TheContext, "function_body", llvmFunction);

  Builder->SetInsertPoint(basicBlock);

  NamedValues.clear();
  for (auto &arg : llvmFunction->args())
    NamedValues[std::string(arg.getName())] = &arg;

  if (children.empty()) {
    // TODO: This might not be what we want. We want something that is functionally equivalent to returning nil.
    Builder->CreateRetVoid();
  } else {
    // NOTE: This wasn't in the tutorial but it appears to generate valid LLVM IR. Tread lightly?
    std::vector<llvm::Value *> values = {};
    for (Node *child : children)
      values.push_back(child->codegen());

    Builder->CreateRet(values.back());
  }

  llvm::verifyFunction(*llvmFunction);
  return llvmFunction;
};

std::string FunctionDeclarationNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "Function Declaration Node: [\n";
  output += padString + "  NAME: " + name + "\n";
  output += padString + "  ARGS:\n";
  output += inspect(arguments, pad + 1) + "\n";
  output += padString + "  BODY:\n";
  output += inspect(children, pad + 1) + "\n";
  output += padString + "]";
  return output;
}

json FunctionDeclarationNode::toJson() {
  json argumentsJson;
  json childJson;

  for (Node *child : children)
    if (child != NULL)
      childJson.push_back(child->toJson());

  for (Node *argument : arguments)
    if (argument != NULL)
      argumentsJson.push_back(argument->toJson());

  json nodeJson = {{"nodeType", "nt_functionDeclaration"},
                   {"arguments", argumentsJson},
                   {"children", childJson}};

  return nodeJson;
};

} // namespace lydianlang
