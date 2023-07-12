#pragma once

namespace sammylang {

void SammyAST::handleCloseParen(ScopeType currentScope) {
  if (inList(currentScope, st_validClosingParenScopes)) {
    popScopes();
  } else {
    throw std::logic_error("Unexpected closing bracket \")\".");
  }
};

} // namespace sammylang

/*
const handleCloseParen = ({ currentScope, pop, token }) => {
  if (
    ![
      st.FUNCTION_CALL_ARGS,
      st.FUNCTION_DEC_ARGS,
      st.GENERIC_EXPRESSION,
      st.IF_CONDITION,
    ].includes(currentScope)
  ) {
    // TODO: Implement test
    throw new Error(
      `Unexpected closing bracket ")" on line ${token.lineNumberStart}`
    )
  }
  pop()
}
*/