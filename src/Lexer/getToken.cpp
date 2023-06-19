#include "../CharacterType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./getStringTokenType.cpp"
#include "./shouldContinueConsumingToken.cpp"

namespace sammylang {

Token *Lexer::getToken() {
  if (charAccumulator.length() == 0)
    return nullptr;

  if (shouldContinueConsumingToken())
    return nullptr;

  TokenType tokenType = tt_NONE;

  if (charAccumulator == "nil") {
    tokenType = tt_nil;
  } else if (charAccumulator == "weak") {
    tokenType = tt_weak;
  } else if (charAccumulator == "if") {
    tokenType = tt_if;
  } else if (charAccumulator == "else") {
    tokenType = tt_else;
  } else if (charAccumulator == "try") {
    tokenType = tt_try;
  } else if (charAccumulator == "handle") {
    tokenType = tt_handle;
  } else if (charAccumulator == "end") {
    tokenType = tt_end;
  } else if (charAccumulator == "function") {
    tokenType = tt_function;
  } else if (charAccumulator == "struct") {
    tokenType = tt_structDefinition;
  } else if (charAccumulator == "enum") {
    tokenType = tt_enumDefinition;
  } else if (charAccumulator == "true" || charAccumulator == "false") {
    tokenType = tt_boolean;
  } else if (charAccumulator == "%[") {
    tokenType = tt_mapOpen;
  } else if (charAccumulator == "->") {
    tokenType = tt_forwardPipe;
  } else if (charAccumulator == "@") {
    tokenType = tt_lambdaOpen;
  } else if (charAccumulator.substr(0, 3) == "<<<") {
    tokenType = tt_comment;
  } else if (charAccumulator == "==" || charAccumulator == "!=" || charAccumulator == ">" ||
             charAccumulator == "<" || charAccumulator == ">=" || charAccumulator == "<=") {
    tokenType = tt_compare;
  } else if (charTypeFrom(charAccumulator[0]) == ct_dollarSign) {
    tokenType = tt_conciseLambdaArgument;
  } else if (charTypeFrom(charAccumulator[0]) == ct_hash) {
    tokenType = tt_comment;
  } else if (latestCharacterType == ct_whitespace) {
    tokenType = tt_whitespace;
  } else if (latestCharacterType == ct_number) {
    tokenType = tt_number;
  } else if (charAccumulator == ".") {
    tokenType = tt_dot;
  } else if (charAccumulator == "=") {
    tokenType = tt_assignment;
  } else if (charAccumulator == ":") {
    tokenType = tt_colon;
  } else if (charAccumulator == ",") {
    tokenType = tt_comma;
  } else if (charAccumulator == "[") {
    tokenType = tt_bracketOpen;
  } else if (charAccumulator == "]") {
    tokenType = tt_bracketClose;
  } else if (charAccumulator == "(") {
    tokenType = tt_parenOpen;
  } else if (charAccumulator == ")") {
    tokenType = tt_parenClose;
  } else if (charAccumulator == "{") {
    tokenType = tt_curlyOpen;
  } else if (charAccumulator == "}") {
    tokenType = tt_curlyClose;
  } else if (charAccumulator == "!") {
    tokenType = tt_bang;
  } else if (charAccumulator == "+" || charAccumulator == "*" || charAccumulator == "/" ||
             charAccumulator == "%" || charAccumulator == "^" || charAccumulator == "||" ||
             charAccumulator == "&&" || charAccumulator == "..") {
    tokenType = tt_operatorInfix;
  } else if (charAccumulator == "-") {
    tokenType = tt_hyphen;
  } else if (latestCharacterType == ct_identifier) {
    tokenType = tt_var;
  } else {
    TokenType stringTokenType = getStringTokenType();
    if (stringTokenType != tt_NONE)
      tokenType = stringTokenType;
  }

  if (tokenType == tt_NONE) {
    std::string squiggles = "";
    for (int index = 0; index < tokenColumnNumberStart - 1; index++) {
      squiggles += " ";
    }
    squiggles += "^";
    std::cout << "charAccumulator is equal to \"^\": " << (charAccumulator == "^") << std::endl;
    throw std::logic_error("Unexpected token " + charAccumulator + "on line " +
                           std::to_string(currentLineNumber) + " :\n" + currentLineValue + "\n" +
                           squiggles);
  }

  Token *token = new Token();
  token->type = tokenType;
  token->value = charAccumulator;
  token->lineNumberStart = tokenLineNumberStart;
  token->columnNumberStart = tokenColumnNumberStart;
  token->lineNumberEnd = currentLineNumber;
  token->columnNumberEnd = currentColumnNumber;

  return token;
};

} // namespace sammylang
