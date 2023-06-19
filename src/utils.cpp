#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#define PRINT_MEMBER(name) print_member_fn(#name, (name))
#include "./InterpolationContextStack/InterpolationContextStack.h"
#include "./Token.cpp"

#pragma once

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
  if (getenv("DEBUG"))
    print(string);
}

void alert(std::string string) { print("\033[1;31m" + string + "\033[0m\n"); };

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

// Helpers for token types
bool isTerminal(TokenType tokenType) { return inList(tokenType, tt_TERMINALS); };
bool isBinaryOperator(TokenType tokenType) { return inList(tokenType, tt_BINARY_OPERATORS); };
bool isUnaryOperator(TokenType tokenType) { return inList(tokenType, tt_UNARY_OPERATORS); };