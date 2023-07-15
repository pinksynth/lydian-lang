#include "./FunctionCallNode.h"
#include "../../../utils.cpp"

#pragma once

namespace sammylang {

void FunctionCallNode::pushToExpressionList(ScopeType scope, Node *node) {
  arguments.push_back(node);
};

std::vector<Node *> FunctionCallNode::getCurrentExpressionList(ScopeType scope) {
  return arguments;
};

std::string FunctionCallNode::inspectString(int pad) {
  std::string padString = getPadString(pad);
  std::string output = padString + "Function Call node: [\n";
  output += padString + "CALLEE:\n";
  output += callee->inspectString(pad + 1) + "\n";
  output += padString + "ARGS:\n";
  output += inspect(arguments, pad + 1) + "\n";
  output += padString + "]";
  return output;
}

json FunctionCallNode::toJson() {
  json argsJson;

  for (Node *arg : arguments)
    if (arg != NULL)
      argsJson.push_back(arg->toJson());

  json nodeJson = {
      {"nodeType", "nt_functionCall"}, {"callee", callee->toJson()}, {"arguments", argsJson}};

  return nodeJson;
};

} // namespace sammylang
