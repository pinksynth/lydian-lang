#pragma once

namespace lydianlang {

void LydianAST::handleKeywordElse() {
  swapScope(st_ifElse);

  // We are consuming the "if" body's closing curly, the "else" keyword, and the "else" opening curly, so increment by 2 extra tokens.
  consumeExtra();
  consumeExtra();
};
} // namespace lydianlang
