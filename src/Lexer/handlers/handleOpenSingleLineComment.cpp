void Lexer::handleOpenSingleLineComment() {
  if (characterType == ct_hash && !stringLiteralMode) {
    singleLineCommentMode = true;
  }
};
