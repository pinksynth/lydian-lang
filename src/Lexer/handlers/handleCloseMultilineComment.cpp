void Lexer::handleCloseMultilineComment() {
  if (characterType != ct_greaterThan)
    return;

  if (stringLiteralMode)
    return;

  if (charAccumulator.length() < 2)
    return;

  std::string lastTwoChars = charAccumulator.substr(charAccumulator.length() - 2);
  if (lastTwoChars == ">>") {
    multilineCommentMode = false;
  }
};
