#define PRINT(string)                                                          \
  if (getenv("DEBUG")) {                                                       \
    std::cout << string << std::endl;                                          \
  };

#include "./InterpolationContextStack/InterpolationContextStack.h"
#include <iostream>

#pragma once
void inspect(InterpolationContextStack ics) {
  std::string icsValue = "[ ";
  for (auto num : ics.body)
    icsValue += std::to_string(num) + " ";
  icsValue += "]";

  PRINT("InterpolationContextStack: " << icsValue);
}
