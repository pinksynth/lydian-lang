#include "./NodeBoolean.h"

std::string NodeBoolean::inspectString(int pad) {
  return "Boolean Node: " + value + " (" + std::to_string(booleanValue) + ")";
};
