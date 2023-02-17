#include "./SammyAST.h"
#include "../NodeType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./Node.h"
#include "./nodeTypes/NodeRoot/NodeRoot.h"
#include <vector>

void SammyAST::fromTokens(std::vector<Token> tokens) {
  NodeRoot root = NodeRoot();
  Node node = root;

  // NOTE: Choosing not to implement a "removeWhitespace" function because we should just be able to continue our loop instead of explicitly traversing the list before walking the AST.
  for (Token token : tokens) {
    debug(token.inspectString());
  }
};
