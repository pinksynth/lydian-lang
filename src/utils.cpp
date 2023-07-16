#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include <fmt/core.h>

#define PRINT_MEMBER(name) lydianlang::print_member_fn(#name, (name))
#include "./InterpolationContextStack/InterpolationContextStack.h"
#include "./Token.cpp"

#pragma once

namespace lydianlang {

int defaultPadding = 60;

bool inList(int needle, std::vector<int> haystack) {
  return std::find(haystack.begin(), haystack.end(), needle) != haystack.end();
};

std::string toString(bool value) { return (value ? "true" : "false"); };
std::string toString(int value) { return std::to_string(value); };
std::string toString(std::vector<int> value) {
  std::string output = "[ ";
  for (int i : value) {
    output += toString(i) + " ";
  }
  output += "]";

  return output;
};

void print(std::string string) { std::cout << string << std::endl; };
void print(bool value) { print(toString(value)); };
void print(int value) { print(toString(value)); };
void print(const char *string) { std::cout << string << std::endl; };

void debug(std::string string) {
#ifdef NDEBUG

#else
  print(string);
#endif
}

void debug(int arg) { debug(toString(arg)); }

std::string alertString(std::string string) { return "\033[1;31m" + string + "\033[0m\n"; };
void alert(std::string string) { print(alertString(string)); };
void alertDebug(std::string string) { debug(alertString(string)); };
std::string highlightString(std::string string) { return "\033[1;34m" + string + "\033[0m\n"; };
void highlight(std::string string) { print(highlightString(string)); };
void highlightDebug(std::string string) { debug(highlightString(string)); };

std::string padded_label(int width, std::string name, std::string value) {
  std::string nameWithColon = name + ":";
  int padSize = width - nameWithColon.size() - value.size();
  if (padSize < 1)
    padSize = 1;
  value.insert(value.begin(), padSize, ' ');
  return nameWithColon + value;
}

std::string print_member_fn(std::string name, std::string value) {
  return padded_label(defaultPadding, name, value);
}

std::string print_member_fn(std::string name, int value) {
  return padded_label(defaultPadding, name, toString(value));
}

std::string print_member_fn(std::string name, bool value) {
  return padded_label(defaultPadding, name, toString(value));
}

std::string charString(char character) {
  if (character == '\n') {
    return "(newline)";
  } else {
    std::string str;
    return str + character;
  }
}

// A helper for replacing values in strings. Taken from:
//   https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string#answer-5878802
void replace_all(std::string &s, std::string const &toReplace, std::string const &replaceWith) {
  std::string buf;
  std::size_t pos = 0;
  std::size_t prevPos;

  // Reserves rough estimate of final size of string.
  buf.reserve(s.size());

  while (true) {
    prevPos = pos;
    pos = s.find(toReplace, pos);
    if (pos == std::string::npos)
      break;
    buf.append(s, prevPos, pos - prevPos);
    buf += replaceWith;
    pos += toReplace.size();
  }

  buf.append(s, prevPos, s.size() - prevPos);
  s.swap(buf);
}

// Taken from https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
std::string getFileString(std::string stringPath) {
  std::ifstream inFile;
  inFile.open(stringPath);

  std::stringstream strStream;
  strStream << inFile.rdbuf();
  return strStream.str();
}

std::string getPadString(int pad = 0) {
  std::string padString = "";
  for (int i = 0; i < pad; i++) {
    padString += "  ";
  }
  return padString;
}

// Helpers for token types
bool isTerminal(TokenType tokenType) { return inList(tokenType, tt_TERMINALS); };
bool isBinaryOperator(TokenType tokenType) { return inList(tokenType, tt_BINARY_OPERATORS); };
bool isUnaryOperator(TokenType tokenType) { return inList(tokenType, tt_UNARY_OPERATORS); };

int operatorPrecedence(std::string op) {
  if (op == "..") {
    return 0;
  }
  if (op == ".") {
    return -1;
  }
  if (op == "^" || op == "%") {
    return -2;
  }
  if (op == "*" || op == "/") {
    return -3;
  }
  if (op == "+" || op == "-") {
    return -4;
  }
  if (op == "==" || op == "!=" || op == ">" || op == "<" || op == ">=" || op == "<=") {
    return -5;
  }
  if (op == "->") {
    return -6;
  }
  if (op == "=") {
    return -7;
  }

  throw std::logic_error(fmt::format("Could not determine precedence for operator {}", op));
}

// Shamelessly copied from:
//   https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
template <typename Base, typename T> inline bool instanceof (const T *ptr) {
  return dynamic_cast<const Base *>(ptr) != nullptr;
}

} // namespace lydianlang
