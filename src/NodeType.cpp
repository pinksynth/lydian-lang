#pragma once

namespace sammylang {

enum NodeType {
  nt_binaryExpression,
  nt_conciseLambdaArgument,
  nt_identifier,
  nt_list,
  nt_literalBoolean,
  nt_literalNumber,
  nt_nil,
  nt_root,
  nt_assignment,
  nt_functionCall
};

std::string nodeString(NodeType nodeType) {
  if (nodeType == nt_binaryExpression)
    return "nt_binaryExpression";
  if (nodeType == nt_conciseLambdaArgument)
    return "nt_conciseLambdaArgument";
  if (nodeType == nt_identifier)
    return "nt_identifier";
  if (nodeType == nt_list)
    return "nt_list";
  if (nodeType == nt_literalBoolean)
    return "nt_literalBoolean";
  if (nodeType == nt_literalNumber)
    return "nt_literalNumber";
  if (nodeType == nt_nil)
    return "nt_nil";
  if (nodeType == nt_root)
    return "nt_root";
  if (nodeType == nt_assignment)
    return "nt_assignment";
  if (nodeType == nt_functionCall)
    return "nt_functionCall";

  throw std::logic_error("Error in AST. Unrecognized Node Type.");
}

} // namespace sammylang