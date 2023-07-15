#include "./FunctionDeclarationNode.h"
#include "../../../utils.cpp"

#pragma once

namespace sammylang {

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
void FunctionDeclarationNode::popCurrentExpressionList() { children.pop_back(); };

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

} // namespace sammylang
