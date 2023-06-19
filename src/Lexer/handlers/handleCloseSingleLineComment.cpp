namespace sammylang {

void Lexer::handleCloseSingleLineComment() {
  if (character == '\n' && singleLineCommentMode) {
    singleLineCommentMode = false;
  }
};

} // namespace sammylang
