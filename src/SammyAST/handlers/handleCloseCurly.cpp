#pragma once

namespace sammylang {

void SammyAST::handleCloseCurly() {
  if (!inList(currentScope, {st_enumDefinition, st_functionDecBody, st_ifBody, st_ifElse,
                             st_lambdaBody, st_structDefinition})) {
    throw std::logic_error("Unexpected token }.");
  }

  popScopes();
};

} // namespace sammylang

/*
const st = require("./scopeTypes")

const handleCloseCurly = ({ currentScope, pop, token }) => {
  if (
    ![
      st.ENUM_DEFINITION,
      st.FUNCTION_DEC_BODY,
      st.IF_BODY,
      st.IF_ELSE,
      st.LAMBDA_BODY,
      st.STRUCT_DEFINITION,
    ].includes(currentScope)
  ) {
    // TODO: Implement test
    throw new Error(
      `Unexpected closing brace "}" on line ${token.lineNumberStart}`
    )
  }
  pop()
}

module.exports = handleCloseCurly
*/