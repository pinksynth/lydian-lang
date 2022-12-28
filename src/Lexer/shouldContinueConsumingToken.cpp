
// const ct = require("../characterTypes")
#include "../CharacterType.cpp"

// Uses the current state and accumulated characters to determine whether the next character should be a part of the current token.
bool Lexer::shouldContinueConsumingToken() {
  // "String literal mode"
  if (stringLiteralMode)
    return true;

  // # Single line comment
  if (singleLineCommentMode)
    return true;

  // <<< Multiline
  //     Comment >>>
  if (multilineCommentMode)
    return true;

  // Adjacent whitespace is grouped together into a single token
  if (latestCharacterType == ct_whitespace && charType == ct_whitespace)
    return true;

  // Alpha characters and underscores are considered part of identifiers
  if ((latestCharacterType == ct_identifier || latestCharacterType == ct_underscore) &&
      (charType == ct_identifier || charType == ct_underscore))
    return true;

  // Concise lambda argument syntax, such as $1 or $23
  if (lambdaArgIdentifierMode && charType == ct_number)
    return true;

  if (numberMode) {
    // Number encountering a period if one has not already been encountered, such as 90.5
    if (charType == ct_period && !numberFloatingPointApplied)
      return true;

    // Number encountering an underscore to be used as a thousands separator, such as in 1_230_000
    if (charType == ct_number || charType == ct_underscore)
      return true;
  }

  // Group "less than" signs together for opening multiline comments: <<<
  if (latestCharacterType == ct_lessThan && charType == ct_lessThan)
    return true;

  // Group "greater than" signs together for opening multiline comments: >>>
  if (latestCharacterType == ct_greaterThan && charType == ct_greaterThan)
    return true;

  // Opening a map literal via "%["
  if (latestCharacterType == ct_percent && charType == ct_leftBracket)
    return true;

  // Assignment via "=", as in "foo = bar"
  if (latestCharacterType == ct_equals && charType == ct_equals)
    return true;

  // Logical "and" via "&&"
  if (latestCharacterType == ct_ampersand && charType == ct_ampersand)
    return true;

  // Logical "or" via "||"
  if (latestCharacterType == ct_pipe && charType == ct_pipe)
    return true;

  // Comparison operators ">=", "<=", and "!="
  if (
      // >=
      (latestCharacterType == ct_greaterThan && charType == ct_equals) ||
      // <=
      (latestCharacterType == ct_lessThan && charType == ct_equals) ||
      // ==
      (latestCharacterType == ct_bang && charType == ct_equals))
    return true;

  // Range operator via ".."
  if (latestCharacterType == ct_period && charType == ct_period)
    return true;

  // Pipe operator via "->"
  if (latestCharacterType == ct_hyphen && charType == ct_greaterThan)
    return true;

  return false;
};
