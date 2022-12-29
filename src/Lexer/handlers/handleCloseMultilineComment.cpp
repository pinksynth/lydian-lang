void Lexer::handleCloseMultilineComment() {
  if (characterType == ct_greaterThan && !stringLiteralMode &&
      charAccumulator.substr(charAccumulator.length() - 2) == ">>") {
    multilineCommentMode = false;
  }
};
