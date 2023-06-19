
// const ct = require("../characterTypes")
#include "../CharacterType.cpp"

namespace sammylang {

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
  if (latestCharacterType == ct_whitespace && characterType == ct_whitespace)
    return true;

  // Alpha characters and underscores are considered part of identifiers
  if ((latestCharacterType == ct_identifier || latestCharacterType == ct_underscore) &&
      (characterType == ct_identifier || characterType == ct_underscore))
    return true;

  // Concise lambda argument syntax, such as $1 or $23
  if (lambdaArgIdentifierMode && characterType == ct_number)
    return true;

  if (numberMode) {
    // Number encountering a period if one has not already been encountered, such as 90.5
    if (characterType == ct_period && !numberFloatingPointApplied)
      return true;

    // Number encountering an underscore to be used as a thousands separator, such as in 1_230_000
    if (characterType == ct_number || characterType == ct_underscore)
      return true;
  }

  // Group "less than" signs together for opening multiline comments: <<<
  if (latestCharacterType == ct_lessThan && characterType == ct_lessThan)
    return true;

  // Group "greater than" signs together for opening multiline comments: >>>
  if (latestCharacterType == ct_greaterThan && characterType == ct_greaterThan)
    return true;

  // Opening a map literal via "%["
  if (latestCharacterType == ct_percent && characterType == ct_leftBracket)
    return true;

  // Assignment via "=", as in "foo = bar"
  if (latestCharacterType == ct_equals && characterType == ct_equals)
    return true;

  // Logical "and" via "&&"
  if (latestCharacterType == ct_ampersand && characterType == ct_ampersand)
    return true;

  // Logical "or" via "||"
  if (latestCharacterType == ct_pipe && characterType == ct_pipe)
    return true;

  // Comparison operators ">=", "<=", and "!="
  if (
      // >=
      (latestCharacterType == ct_greaterThan && characterType == ct_equals) ||
      // <=
      (latestCharacterType == ct_lessThan && characterType == ct_equals) ||
      // ==
      (latestCharacterType == ct_bang && characterType == ct_equals))
    return true;

  // Range operator via ".."
  if (latestCharacterType == ct_period && characterType == ct_period)
    return true;

  // Pipe operator via "->"
  if (latestCharacterType == ct_hyphen && characterType == ct_greaterThan)
    return true;

  return false;
};

} // namespace sammylang
