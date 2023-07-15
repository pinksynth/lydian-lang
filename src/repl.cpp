#include <fstream>
#include <iostream>
#include <string>

#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include "./SammyAST/SammyAST.cpp"

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

  std::cout << sammylang::highlightString("Welcome to SammyLang") << std::endl;

  while (true) {
    std::cout << std::endl << "> ";
    std::string input;
    std::getline(std::cin, input);
    std::cout << input << std::endl;
    sammylang::Lexer lexer = sammylang::Lexer();
    std::vector<sammylang::Token> tokens = lexer.lex(input);
    sammylang::SammyAST ast = sammylang::SammyAST();
    ast.fromTokens(tokens);
    std::cout << "JSON Output from AST:" << std::endl;
    std::cout << ast.jsonAST.dump(2) << std::endl;
  }

  return 0;
}
