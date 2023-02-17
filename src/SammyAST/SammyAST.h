#include "../Token.cpp"
#include <vector>

#pragma once
class SammyAST {

public:
  void fromTokens(std::vector<Token> tokens);
};
