#include "../nodeTypes/FunctionDeclarationNode/FunctionDeclarationNode.cpp"

#pragma once

namespace sammylang {

void SammyAST::handleFunctionDefinitionName() {
  scopes.push_back(st_functionDecArgs);
  FunctionDeclarationNode *functionDeclarationNode = new FunctionDeclarationNode();
  functionDeclarationNode->name = nextToken.value;
  functionDeclarationNode->parent = node;
  node->pushToExpressionList(currentScope, functionDeclarationNode);
  node = functionDeclarationNode;

  // Consume the identifier. E.g., "foo" in "fn foo("
  consumeExtra();
  // Consume the open paren. E.g., "(" in "fn foo("
  consumeExtra();
};

} // namespace sammylang

/*
const nt = require("./nodeTypes")
const st = require("./scopeTypes")
const tt = require("../tokenTypes")

const handleFunctiondefinitionName = ({
  consumeExtra,
  nextToken,
  node,
  pushToExpressionList,
  scopes,
  setNode,
  thirdTokenType,
  token,
}) => {
  if (thirdTokenType !== tt.PAREN_OPEN) {
    // TODO: Implement test
    throw new Error(
      `Syntax Error for function ${nextToken.value} on line ${token.lineNumberStart}`
    )
  }
  scopes.push(st.FUNCTION_DEC_ARGS)
  const child = {
    args: [],
    children: [],
    parent: node,
    name: nextToken.value,
    type: nt.FUNCTION_DEFINITION,
    lineNumberStart: token.lineNumberStart,
    columnNumberStart: token.columnNumberStart,
  }
  pushToExpressionList(child)
  setNode(child)

  // For named function definitions, we have consumed the keyword, the name, and the opening paren fot the args, so we'll manually increment the tokens by an extra 2.
  consumeExtra()
  consumeExtra()
}

module.exports = handleFunctiondefinitionName
*/