#include "./NodeNumber.h"

std::string NodeNumber::inspectString(int pad) {
  return "Number Node: " + value + " (" + std::to_string(doubleValue) + ")";
};
