namespace lydianlang {

void Lexer::handleCloseLambdaArgIdentifierMode() {
  if (lambdaArgIdentifierMode && characterType != ct_number) {
    lambdaArgIdentifierMode = false;
  }
};

} // namespace lydianlang
