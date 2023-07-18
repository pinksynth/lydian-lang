#include "./IfExpressionNode.h"
#include "../../../utils.cpp"

#pragma once

namespace lydianlang {

std::vector<Node *> IfExpressionNode::getCurrentExpressionList(ScopeType scope) {
  switch (scope) {
  case st_ifCondition:
    return condition;
  case st_ifBody:
    return bodyChildren;
  case st_ifElse:
    return elseChildren;

  default:
    throw std::logic_error("Internal AST error. Invalid scope for 'if' expression: " +
                           scopeString(scope));
    break;
  }
};

void IfExpressionNode::pushToExpressionList(ScopeType scope, Node *node) {
  switch (scope) {
  case st_ifCondition:
    condition.push_back(node);
    break;
  case st_ifBody:
    bodyChildren.push_back(node);
    break;
  case st_ifElse:
    elseChildren.push_back(node);
    break;

  default:
    throw std::logic_error("Internal AST error. Invalid scope for 'if' expression: " +
                           scopeString(scope));
    break;
  }
};

void IfExpressionNode::popCurrentExpressionList(ScopeType scope) {
  switch (scope) {
  case st_ifCondition:
    condition.pop_back();
    break;
  case st_ifBody:
    bodyChildren.pop_back();
    break;
  case st_ifElse:
    elseChildren.pop_back();
    break;

  default:
    throw std::logic_error("Internal AST error. Invalid scope for 'if' expression: " +
                           scopeString(scope));
    break;
  }
};

llvm::Value *IfExpressionNode::codegen() { throw std::logic_error("Almost there!"); }
//   std::vector<llvm::Type *> argTypes(arguments.size(), llvm::Type::getDoubleTy(*TheContext));

//   llvm::FunctionType *functionType =
//       llvm::FunctionType::get(llvm::Type::getDoubleTy(*TheContext), argTypes, false);

//   llvm::Function *llvmFunction =
//       llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, name, TheModule.get());

//   // Set names for all arguments.
//   unsigned argIndex = 0;
//   for (auto &llvmFunctionArg : llvmFunction->args()) {
//     Node *argumentBaseNode = arguments[argIndex++];
//     IdentifierNode *argumentIdentifierNode = dynamic_cast<IdentifierNode *>(argumentBaseNode);

//     if (argumentIdentifierNode == nullptr)
//       throw std::logic_error("Only identifier arguments are supported at this time. Found type: " +
//                              nodeString(argumentBaseNode->nodeType));

//     llvmFunctionArg.setName(argumentIdentifierNode->value);
//   }

//   llvm::BasicBlock *basicBlock =
//       llvm::BasicBlock::Create(*TheContext, "function_body", llvmFunction);

//   Builder->SetInsertPoint(basicBlock);

//   NamedValues.clear();
//   for (auto &arg : llvmFunction->args())
//     NamedValues[std::string(arg.getName())] = &arg;

//   if (children.empty()) {
//     // TODO: This might not be what we want. We want something that is functionally equivalent to returning nil.
//     Builder->CreateRetVoid();
//   } else {
//     // TODO: Support actual blocks instead of one child at the end of the body.
//     Node *backChild = children.back();
//     llvm::Value *returnValue = backChild->codegen();
//     Builder->CreateRet(returnValue);
//   }

//   llvm::verifyFunction(*llvmFunction);
//   return llvmFunction;
// };

std::string IfExpressionNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "If Expression Node: [\n";
  output += padString + "  CONDITION:\n";
  output += inspect(condition, pad + 1) + "\n";
  output += padString + "  BODY:\n";
  output += inspect(bodyChildren, pad + 1) + "\n";
  output += padString + "  ELSE:\n";
  output += inspect(elseChildren, pad + 1) + "\n";
  output += padString + "]";
  return output;
}

json IfExpressionNode::toJson() {
  json conditionJson;
  json bodyJson;
  json elseJson;

  for (Node *child : condition)
    if (child != NULL)
      conditionJson.push_back(child->toJson());

  for (Node *child : bodyChildren)
    if (child != NULL)
      bodyJson.push_back(child->toJson());

  for (Node *child : elseChildren)
    if (child != NULL)
      elseJson.push_back(child->toJson());

  json nodeJson = {{"nodeType", nodeString(nodeType)},
                   {"condition", conditionJson},
                   {"bodyChildren", bodyJson},
                   {"elseChildren", elseJson}};

  return nodeJson;
};

} // namespace lydianlang
