#include "../InterpolationContextStack/InterpolationContextStack.h"
#include <iostream>
#include <vector>

class Lexer {
  std::string charAccumulator = "";
  int currentColumnNumber = 1;
  int currentLineNumber = 1;
  std::string currentLineValue = "";
  std::string input;
  bool lambdaArgIdentifierMode = false;
  bool multilineCommentMode = false;
  bool numberFloatingPointApplied = false;
  bool numberMode = false;
  bool singleLineCommentMode = false;
  bool stringLiteralMode = false;
  int tokenColumnNumberStart = 1;
  int tokenLineNumberStart = 1;
  // tokens: [],
  InterpolationContextStack ics;

  void resetState();

  // Debugging
  void printCharInfo(char character);

public:
  void lex(std::string input);

  // Debugging (public)
  void inspect();
};
