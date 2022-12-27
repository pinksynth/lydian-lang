#define PRINT(string)                                                          \
  if (getenv("DEBUG")) {                                                       \
    std::cout << string << std::endl;                                          \
  };

#include "./InterpolationContextStack/InterpolationContextStack.h"
#include <iostream>

#pragma once
void inspect(InterpolationContextStack ics) {
  std::string icsValue = "[ ";
  while (!ics.body.empty()) {
    // We do pop() here because we have a copy of ICS, not a reference.
    icsValue += std::to_string(ics.body.top()) + " ";
    ics.body.pop();
  }
  icsValue += "]";

  PRINT("InterpolationContextStack: " << icsValue);
}
