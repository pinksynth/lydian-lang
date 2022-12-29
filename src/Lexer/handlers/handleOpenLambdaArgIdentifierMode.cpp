void Lexer::handleOpenLambdaArgIdentifierMode() {
  if (charAccumulator.length() == 0 && characterType == ct_dollarSign) {
    lambdaArgIdentifierMode = true;
  }
};
