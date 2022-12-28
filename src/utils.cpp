#define PRINT_MEMBER(name) print_member_fn(#name, (name))
#include "./InterpolationContextStack/InterpolationContextStack.h"
#include <iostream>

int defaultPadding = 60;

void print(std::string string) {
  if (getenv("DEBUG")) {
    std::cout << string << std::endl;
  }
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
  return padded_label(defaultPadding, name, std::to_string(value));
}

std::string print_member_fn(std::string name, bool value) {
  std::string stringValue(value ? "true" : "false");
  return padded_label(defaultPadding, name, stringValue);
}
