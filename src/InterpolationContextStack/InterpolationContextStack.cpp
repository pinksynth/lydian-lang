#include "./InterpolationContextStack.h"
#include <iostream>

InterpolationContextStack::InterpolationContextStack() {
  body = {0, 1, 2, 0, 3};
  PRINT("Initializing ICS");
};
