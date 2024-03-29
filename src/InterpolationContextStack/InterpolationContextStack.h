#include <stack>

#pragma once

namespace lydianlang {

class InterpolationContextStack {

public:
  std::stack<int> body;

  InterpolationContextStack();
  int top();
  void decrementContext();
  void incrementContext();
  void popContext();
  void pushContext();

  // Debugging
  std::string inspectString();

private:
  void updateHead(int newValue);
};

} // namespace lydianlang
