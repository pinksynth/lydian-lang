#include "../NodeType.cpp"

class Node {

public:
  NodeType nodeType;
  Node(NodeType theNodeType) { nodeType = theNodeType; }
};