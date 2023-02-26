#include "./SammyAST.h"
#include "../NodeType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./Node.cpp"
#include "./nodeTypes/NodeRoot/NodeRoot.cpp"
#include <vector>

void SammyAST::fromTokens(std::vector<Token> tokens) {
  NodeRoot root = NodeRoot();
  Node *node = &root;

  // NOTE: Choosing not to implement a "removeWhitespace" function because we should just be able to continue our loop instead of explicitly traversing the list before walking the AST.

  size_t tokensCount = tokens.size();
  for (size_t i = 0; i < tokensCount; i++) {
    Token token = tokens[i];
    TokenType tokenType = token.type;

    // Ignore all whitespace. This language only uses whitespace at the lexer level, not the AST level.
    if (tokenType == tt_whitespace)
      continue;

    Token nextToken;
    TokenType nextTokenType;
    Token thirdToken;
    TokenType thirdTokenType;

    if (i != tokensCount - 1) {
      nextToken = tokens[i + 1];
      nextTokenType = nextToken.type;
    }

    if (i != tokensCount - 2) {
      thirdToken = tokens[i + 2];
      thirdTokenType = thirdToken.type;
    }

    // if (TT_TERMINALS.includes(tokenType) && !TT_BINARY_OPERATORS.includes(nextTokenType)) {
    //   node.children.push(getNodeFromToken(token))
    // }

    std::cout << "Token type:" << std::endl;
    print(std::to_string(tokenType));
    std::cout << "Haystack:" << std::endl;
    for (int i : tt_TERMINALS)
      print(std::to_string(i));

    print(std::to_string(isTerminal(tokenType)));
    if (isTerminal(tokenType)) {
      // Get node from token and push onto children.
      std::cout << "Pushing..." << std::endl;
      node->pushToExpressionList(getNodeFromToken(token));
    }

    print(token.inspectString());
  }

  std::cout << "AST:" << std::endl;
  print(node->inspectString());
};

Node SammyAST::getNodeFromToken(Token token) {
  Node node = Node();
  return node;
};