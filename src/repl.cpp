#include <fstream>
#include <iostream>
#include <string>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./LydianAST/LydianAST.cpp"

void signalCallbackHandler(int signum) {
  if (signum == 2) {
    std::cout << std::endl << "Goodbye!" << std::endl;

    exit(0);
  } else {
    exit(1);
  }
}

int main() {
  signal(SIGINT, signalCallbackHandler);

  std::cout << lydianlang::highlightString("Welcome to LydianLang") << std::endl;
  int lineNumber = 1;

  while (true) {
    std::cout << std::endl << "𝐋" << std::to_string(lineNumber) << "> ";
    std::string input;
    std::getline(std::cin, input);
    std::cout << input << std::endl;
    lydianlang::Lexer lexer = lydianlang::Lexer();
    std::vector<lydianlang::Token> tokens = lexer.lex(input);
    lydianlang::LydianAST ast = lydianlang::LydianAST();
    ast.fromTokens(tokens);
    std::cout << "JSON Output from AST:" << std::endl;
    std::cout << ast.jsonAST.dump(2) << std::endl;

    lineNumber = lineNumber + 1;
  }

  return 0;
}
