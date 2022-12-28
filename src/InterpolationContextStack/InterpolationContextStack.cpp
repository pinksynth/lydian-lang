/*
Used by the lexer to keep track of curly braces seen while in string interpolation. `body` is an array of counters. The number of counters in the stack corresponds to how many contexts deep we are in string interpolation. The value of each counter corresponds to how many unclosed lefthand curly braces have been encountered in the current context.

The following demonstrates how this stack is used by the lexer (also see notes in `handleStrings.cpp`):

"a { b(@{ "c { d } e" }) }"
^
At this token, the stack looks like: []
Because we have not entered into any interpolation contexts.

"a { b(@{ "c { d } e" }) }"
     ^
     At this token, the stack looks like: [0]
     Because we entered into an interpolation context but haven't seen any curly braces.

"a { b(@{ "c { d } e" }) }"
          ^
          At this token, the stack looks like: [1]
          Because we entered into an interpolation context and saw a curly brace for the lambda. We will need a corresponding righthand brace before we 

"a { b(@{ "c { d } e" }) }"
               ^
               At this token, the stack looks like: [1, 0]
               Because we entered into an additional interpolation context but haven't seen any curly braces in the new context.

"a { b(@{ "c { d } e" }) }"
                 ^
                 At this token, the stack looks like: [1]
                 Because we popped exited the innermost interpolation context. We'll still need to see an additional righthand curly before we're ready to pop the new context.

"a { b(@{ "c { d } e" }) }"
                      ^
                      At this token, the stack looks like: [0]
                      Because we found the extra righthand curly brace we needed before we could pop the current interpolation context.

"a { b(@{ "c { d } e" }) }"
                         ^
                         At this token, the stack looks like: []
                         Because we found the righthand curly brace we needed to exit the outermost interpolation context. Now we are not in an interpolation context.
*/

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
