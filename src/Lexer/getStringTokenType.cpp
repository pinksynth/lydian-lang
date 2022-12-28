#include "../CharacterType.cpp"

/* NOTE: When generating tokens, we use four token types for strings which correspond to the presence of interpolations:
STRING_PURE:            No interpolation. String starts with " and ends with ".
STRING_INTERP_BEFORE:   Before interpolation. String starts with " and ends with {.
STRING_INTERP_BETWEEN:  Between interpolations. String starts with } and ends with {.
STRING_INTERP_AFTER:    After interpolations. String starts with } and ends with ".
So for the following expression:
    "a { b "c" } d { e } f"
The tokens would be:
    <tokenType: STRING_INTERP_BEFORE    value: "a {  >
    <tokenType: VAR                     value: b     >
    <tokenType: STRING_PURE             value: "c"   >
    <tokenType: STRING_INTERP_BETWEEN   value: } d { >
    <tokenType: VAR                     value: e     >
    <tokenType: STRING_INTERP_AFTER     value: } f"  >
*/
TokenType Lexer::getStringTokenType() {
  // First character type
  CharacterType ct1 = charTypeFrom(charAccumulator[0]);
  // Last character type
  CharacterType ct2 = charTypeFrom(charAccumulator[charAccumulator.length() - 1]);

  if (ct1 == ct_doubleQuote && ct2 == ct_doubleQuote) {
    return tt_stringPure;
  } else if (ct1 == ct_doubleQuote && ct2 == ct_leftCurly) {
    return tt_stringInterpBefore;
  } else if (ct1 == ct_rightCurly && ct2 == ct_leftCurly) {
    return tt_stringInterpBetween;
  } else if (ct1 == ct_rightCurly && ct2 == ct_doubleQuote) {
    return tt_stringInterpAfter;
  }

  return tt_NONE;
};
