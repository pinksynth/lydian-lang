namespace lydianlang {

void Lexer::handleStrings() {
  if (multilineCommentMode || singleLineCommentMode) {
    return;
  }

  if (characterType == ct_doubleQuote) {
    if (stringLiteralMode) {
      if (previousCharacterType != ct_backslash) {
        // Found unescaped double quote inside string literal mode. Exit string literal mode.
        stringLiteralMode = false;
      }
    } else {
      // Found double quote outside string literal mode. Enter string literal mode.
      stringLiteralMode = true;
    }
  } else if (characterType == ct_leftCurly) {
    if (stringLiteralMode) {
      if (previousCharacterType != ct_backslash) {
        // Found unescaped left curly while in string literal mode. Exit string literal mode and an interpolation context to the stack.
        stringLiteralMode = false;
        ics.pushContext();
      }
    } else {
      // Found left curly while not in string literal mode. Increment the current interpolation context counter. For example, if this is the third curly we've seen since entering the context, we'll need three corresponding righthand curlies before before we can leave the interpolation context and go back to string mode.
      ics.incrementContext();
    }
  } else if (characterType == ct_rightCurly) {
    if (!stringLiteralMode) {
      // Encountered righthand curly when not in string literal mode.
      if (ics.top() == 0) {
        // We have 0 unclosed lefthand curlies, so this righthand curly means we're re-entering string mode and popping the current interpolation context.
        ics.popContext();
        stringLiteralMode = true;
      } else {
        // We still have to see more righthand curlies before we're ready to re-enter string mode.
        ics.decrementContext();
      }
    }
  }
};

} // namespace lydianlang
