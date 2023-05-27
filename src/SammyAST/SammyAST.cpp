#include "./SammyAST.h"
#include "../NodeType.cpp"
#include "../Token.cpp"
#include "../TokenType.cpp"
#include "./Node.cpp"
#include "./nodeTypes/BooleanNode/BooleanNode.cpp"
#include "./nodeTypes/ConciseLambdaArgNode/ConciseLambdaArgNode.cpp"
#include "./nodeTypes/IdentifierNode/IdentifierNode.cpp"
#include "./nodeTypes/NilNode/NilNode.cpp"
#include "./nodeTypes/NumberNode/NumberNode.cpp"
#include "./nodeTypes/RootNode/RootNode.cpp"
#include <vector>

void SammyAST::fromTokens(std::vector<Token> tokens) {
  RootNode root = RootNode();
  Node *node = &root;

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

    if (tokenType == tt_bracketOpen) {
      // child = new ListNode();
    }
    if (tokenType == tt_bracketClose) {
    }
    if (isTerminal(tokenType) && !isBinaryOperator(nextTokenType)) {
      // Get node from token and push onto children.
      Node *child = getTerminalNodeFromToken(token);
      node->pushToExpressionList(child);
    }

    print(token.inspectString());
  }

  std::cout << "AST:" << std::endl;
  print(node->inspectString());
};

Node *SammyAST::getTerminalNodeFromToken(Token token) {
  switch (token.type) {
  case tt_var:
    return new IdentifierNode(token);

  case tt_number:
    return new NumberNode(token);

  case tt_boolean:
    return new BooleanNode(token);

  case tt_nil:
    return new NilNode();

  case tt_conciseLambdaArgument:
    return new ConciseLambdaArgNode(token);

  default:
    // throw std::out_of_range("Encountered an unknown token type.");
    // break;
    return new Node();
  }
};