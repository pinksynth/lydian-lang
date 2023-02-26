#include <algorithm>
#include <vector>

// TODO: Definitely namespace this stuff 😅
#pragma once
enum TokenType {
  tt_NONE,
  tt_assignment,
  tt_bang,
  tt_boolean,
  tt_bracketClose,
  tt_bracketOpen,
  tt_colon,
  tt_comma,
  tt_comment,
  tt_compare,
  tt_conciseLambdaArgument,
  tt_curlyClose,
  tt_curlyOpen,
  tt_dot,
  tt_else,
  tt_end,
  tt_enumDefinition,
  tt_forwardPipe,
  tt_function,
  tt_handle,
  tt_hyphen,
  tt_if,
  tt_lambdaOpen,
  tt_mapOpen,
  tt_null,
  tt_number,
  tt_operatorInfix,
  tt_parenClose,
  tt_parenOpen,
  tt_stringInterpAfter,
  tt_stringInterpBefore,
  tt_stringInterpBetween,
  tt_stringPure,
  tt_structDefinition,
  tt_try,
  tt_var,
  tt_weak,
  tt_whitespace
};

std::vector<int> tt_TERMINALS = {tt_boolean, tt_conciseLambdaArgument, tt_null, tt_number, tt_var};

std::vector<int> tt_BINARY_OPERATORS = {tt_assignment,  tt_compare, tt_dot,
                                        tt_forwardPipe, tt_hyphen,  tt_operatorInfix};

std::vector<int> tt_UNARY_OPERATORS = {tt_hyphen, tt_bang};

bool inList(int needle, std::vector<int> haystack) {
  return std::find(haystack.begin(), haystack.end(), needle) != haystack.end();
};

bool isTerminal(TokenType tokenType) { return inList(tokenType, tt_TERMINALS); };

bool isBinaryOperator(TokenType tokenType) { return inList(tokenType, tt_BINARY_OPERATORS); };

bool isUnaryOperator(TokenType tokenType) { return inList(tokenType, tt_UNARY_OPERATORS); };