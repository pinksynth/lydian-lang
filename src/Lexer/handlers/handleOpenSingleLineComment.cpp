namespace sammylang {

void Lexer::handleOpenSingleLineComment() {
  if (characterType == ct_hash && !stringLiteralMode) {
    singleLineCommentMode = true;
  }
};

} // namespace sammylang
