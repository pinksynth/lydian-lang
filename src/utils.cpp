#define PRINT_MEMBER(name) print_member_fn(#name, (name))
#include "./InterpolationContextStack/InterpolationContextStack.h"
#include "./Token.cpp"
#include <iostream>

int defaultPadding = 60;

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

void debug(std::string string) {
  if (getenv("DEBUG"))
    print(string);
}

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