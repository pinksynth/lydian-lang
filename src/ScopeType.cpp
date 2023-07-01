#include <vector>

#include "./utils.cpp"

#pragma once

namespace sammylang {

enum ScopeType {
  st_array,
  st_assignment,
  st_binaryOperator,
  st_enumDefinition,
  st_functionCallArgs,
  st_functionDecArgs,
  st_functionDecBody,
  st_genericExpression,
  st_ifBody,
  st_ifCondition,
  st_ifElse,
  st_lambdaArgs,
  st_lambdaBody,
  st_mapKey,
  st_mapValue,
  st_root,
  st_string,
  st_stringInterpolation,
  st_structDefinition,
  st_structKey,
  st_structValue,
  st_tryBody,
  st_tryHandlerBody,
  st_tryHandlerPattern,
  st_unaryOperator,
};

std::vector<int> st_operandScopeTypes = {st_assignment, st_binaryOperator, st_unaryOperator};

std::string scopeString(ScopeType scopeType) {
  if (scopeType == st_array)
    return "array";
  if (scopeType == st_assignment)
    return "assignment";
  if (scopeType == st_binaryOperator)
    return "binaryOperator";
  if (scopeType == st_enumDefinition)
    return "enumDefinition";
  if (scopeType == st_functionCallArgs)
    return "functionCallArgs";
  if (scopeType == st_functionDecArgs)
    return "functionDecArgs";
  if (scopeType == st_functionDecBody)
    return "functionDecBody";
  if (scopeType == st_genericExpression)
    return "genericExpression";
  if (scopeType == st_ifBody)
    return "ifBody";
  if (scopeType == st_ifCondition)
    return "ifCondition";
  if (scopeType == st_ifElse)
    return "ifElse";
  if (scopeType == st_lambdaArgs)
    return "lambdaArgs";
  if (scopeType == st_lambdaBody)
    return "lambdaBody";
  if (scopeType == st_mapKey)
    return "mapKey";
  if (scopeType == st_mapValue)
    return "mapValue";
  if (scopeType == st_root)
    return "root";
  if (scopeType == st_string)
    return "string";
  if (scopeType == st_stringInterpolation)
    return "stringInterpolation";
  if (scopeType == st_structDefinition)
    return "structDefinition";
  if (scopeType == st_structKey)
    return "structKey";
  if (scopeType == st_structValue)
    return "structValue";
  if (scopeType == st_tryBody)
    return "tryBody";
  if (scopeType == st_tryHandlerBody)
    return "tryHandlerBody";
  if (scopeType == st_tryHandlerPattern)
    return "tryHandlerPattern";
  if (scopeType == st_unaryOperator)
    return "unaryOperator";

  throw std::logic_error("Error in AST. Unrecognized scope type");
}

void debugScopes(std::vector<ScopeType> scopeTypes) {
  std::string scopesString = "Scopes: { ";
  for (ScopeType scopeType : scopeTypes) {
    scopesString += scopeString(scopeType) + ", ";
  }
  scopesString += "}\n";

  debug(scopesString);
}

} // namespace sammylang