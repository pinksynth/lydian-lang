#include "./InterpolationContextStack.h"
#include <iostream>

InterpolationContextStack::InterpolationContextStack(){};

int InterpolationContextStack::top() { return body.top(); };
void InterpolationContextStack::decrementContext() {
  int previousValue = body.top();
  if (previousValue == 0) {
    throw std::logic_error(
        "Error in lexer. Could not decrement interpolation context.");
  }
  int newValue = previousValue - 1;
  updateHead(newValue);
};
void InterpolationContextStack::incrementContext() {
  int previousValue = body.top();
  updateHead(previousValue + 1);
};
void InterpolationContextStack::popContext() {
  if (body.top() != 0) {
    throw std::logic_error(
        "Error in lexer. Could not pop interpolation context.");
  }
  body.pop();
};
void InterpolationContextStack::pushContext() { body.push(0); };
void InterpolationContextStack::updateHead(int newValue) {
  body.pop();
  body.push(newValue);
};
