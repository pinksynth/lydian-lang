namespace lydianlang {

void Lexer::handleCloseSingleLineComment() {
  if (character == '\n' && singleLineCommentMode) {
    singleLineCommentMode = false;
  }
};

} // namespace lydianlang
