#include "./TokenType.cpp"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// NOTE: A struct might make more sense for this.
#pragma once
class Token {

public:
  TokenType type = tt_NONE;
  std::string value = "";

  // Meta
  int lineNumberStart = 0;
  int columnNumberStart = 0;
  int lineNumberEnd = 0;
  int columnNumberEnd = 0;

  Token(){};
  Token(std::string t_value, TokenType t_type, int t_lineNumberStart, int t_columnNumberStart,
        int t_lineNumberEnd, int t_columnNumberEnd) {
    value = t_value;
    type = t_type;
    lineNumberStart = t_lineNumberStart;
    columnNumberStart = t_columnNumberStart;
    lineNumberEnd = t_lineNumberEnd;
    columnNumberEnd = t_columnNumberEnd;
  };

  std::string inspectString(bool detailed = false) const {
    std::string message = "Token: ";
    message += value;
    if (detailed) {
      message += "(";
      message += "type: ";
      message += std::to_string(type);
      message += "; lineNumberStart: ";
      message += std::to_string(lineNumberStart);
      message += "; columnNumberStart: ";
      message += std::to_string(columnNumberStart);
      message += "; lineNumberEnd: ";
      message += std::to_string(lineNumberEnd);
      message += "; columnNumberEnd: ";
      message += std::to_string(columnNumberEnd);
      message += ")";
    }
    return message;
  };

  json toJson() {
    json tokenJson = {{"type", type},
                      {"value", value},
                      {"lineNumberStart", lineNumberStart},
                      {"columnNumberStart", columnNumberStart},
                      {"lineNumberEnd", lineNumberEnd},
                      {"columnNumberEnd", columnNumberEnd}};

    return tokenJson;
  };
};

std::ostream &operator<<(std::ostream &os, const Token &token) {
  std::string str = token.inspectString(true);
  os << str;
  return os;
}

bool operator==(const Token &tokenA, const Token &tokenB) {
  return tokenA.type == tokenB.type && tokenA.value == tokenB.value &&
         tokenA.lineNumberStart == tokenB.lineNumberStart &&
         tokenA.columnNumberStart == tokenB.columnNumberStart &&
         tokenA.lineNumberEnd == tokenB.lineNumberEnd &&
         tokenA.columnNumberEnd == tokenB.columnNumberEnd;
}
