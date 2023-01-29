#include "../src/utils.cpp"
#include "./InterpolationContextStack/InterpolationContextStack.cpp"
#include "./Lexer/Lexer.cpp"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string testInput = R"sammy(
a = 1 + 2
)sammy";

int main() {
  // Print some "hello world" JSON to the console to prove it works.
  json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");

  std::cout << ex1;

  print("Compiling...");
  Lexer lexer = Lexer();
  lexer.lex(testInput);

  return 0;
};
