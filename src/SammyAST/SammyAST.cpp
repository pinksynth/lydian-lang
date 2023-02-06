#include "./SammyAST.h"
#include "../NodeType.cpp"
#include "../Token.cpp"
#include "./Node.h"
#include <vector>

void SammyAST::fromTokens(std::vector<Token> tokens) {
  for (Token token : tokens) {
    debug(token.inspectString());
    Node node = Node(nt_NONE);
  }
};
