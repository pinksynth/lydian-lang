void Lexer::handleRangeOperator() {
  // If encountering a period followed by another period, turn off number mode because this will be a range operator (..)
  if (numberMode && nextCharacterType == ct_period && thirdCharacterType == ct_period) {
    numberMode = false;
  }
};
