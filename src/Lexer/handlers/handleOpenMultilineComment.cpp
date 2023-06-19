namespace sammylang {

void Lexer::handleOpenMultilineComment() {
  if (characterType == ct_lessThan && !stringLiteralMode && !singleLineCommentMode &&
      charAccumulator == "<<") {
    multilineCommentMode = true;
  }
};

} // namespace sammylang
