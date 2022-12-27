#include <vector>

#pragma once
class InterpolationContextStack {

public:
  std::vector<int> body;

  InterpolationContextStack();
  int peek();
  void decrementContext();
  void incrementContext();
  void popContext();
  void pushContext();
};
