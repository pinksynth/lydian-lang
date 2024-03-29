// TODO: Figure out how the heck to print enum cases by name during runtime.
#pragma once

namespace lydianlang {

enum CharacterType {
  ct_NONE,
  ct_ampersand,
  ct_asterisk,
  ct_atSign,
  ct_backslash,
  ct_bang,
  ct_caret,
  ct_colon,
  ct_comma,
  ct_dollarSign,
  ct_doubleQuote,
  ct_equals,
  ct_greaterThan,
  ct_hash,
  ct_hyphen,
  ct_identifier,
  ct_leftBracket,
  ct_leftCurly,
  ct_leftParen,
  ct_lessThan,
  ct_number,
  ct_percent,
  ct_period,
  ct_pipe,
  ct_plusSign,
  ct_rightBracket,
  ct_rightCurly,
  ct_rightParen,
  ct_singleQuote,
  ct_slash,
  ct_underscore,
  ct_whitespace
};

}