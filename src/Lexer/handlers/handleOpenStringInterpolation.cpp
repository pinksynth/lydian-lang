namespace lydianlang {

void Lexer::handleOpenStringInterpolation() {
  if (!stringLiteralMode)
    return;

  bool isEscaped = previousCharacterType == ct_backslash;
  if (isEscaped)
    return;

  bool isInterpolation = characterType == ct_leftCurly;
  if (isInterpolation)
    stringLiteralMode = false;
};

} // namespace lydianlang
