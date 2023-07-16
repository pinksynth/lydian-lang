namespace lydianlang {

void Lexer::handleEndNumberMode() {
  if (numberMode && characterType != ct_number && characterType != ct_underscore &&
      characterType != ct_period) {
    numberMode = false;
    numberFloatingPointApplied = false;
  }
};

} // namespace lydianlang
