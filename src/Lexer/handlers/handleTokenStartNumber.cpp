namespace sammylang {

void Lexer::handleTokenStartNumber() {
  if (charAccumulator.length() == 0 && characterType == ct_number) {
    numberMode = true;
  }
};

} // namespace sammylang
