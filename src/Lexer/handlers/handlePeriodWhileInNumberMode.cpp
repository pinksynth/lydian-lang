namespace sammylang {

void Lexer::handlePeriodWhileInNumberMode() {
  // If encountering a period in number mode, assume it is our decimal point.
  if (numberMode && characterType == ct_period) {
    if (numberFloatingPointApplied) {
      numberMode = false;
      numberFloatingPointApplied = false;
      // If we've already placed our decimal point and see another dot, it's a new token.
    } else {
      numberFloatingPointApplied = true;
    }
  }
};

} // namespace sammylang
