#include "../Node.cpp"
#include "../nodeTypes/AssignmentNode/AssignmentNode.cpp"
#include "../nodeTypes/BinaryExpressionNode/BinaryExpressionNode.cpp"

namespace lydianlang {

void LydianAST::handleBinaryOperator() {
  // debug("Handling binary operator...");
  ScopeType prevScope = scopes.back();
  currentExpressionList = node->getCurrentExpressionList(prevScope);
  scopes.push_back(st_binaryOperator);

  // When we encounter a binary operator, it means that the previous sibling must be treated not as its own statement, but rather an operand of this operator.
  Node *leftOperand = currentExpressionList.back();
  currentExpressionList.pop_back();
  node->popCurrentExpressionList(currentScope);

  // Here we do some swapping to handle operator precedence.
  // That is, we check to see if we found 2 + 3 * 4.
  // The algorithm wants this to be ((2 + 3) * 4).
  // So we have to tell it to be (2 + (3 * 4)).
  // In order to do this, we take the left operand ((2 + 3)) and check if it is a binary expression with a lower-priority operator. If it is, then we instead replace the whole node with its lefthand operand (2).
  BinaryExpressionNode *binaryExpressionLeftOperand =
      dynamic_cast<BinaryExpressionNode *>(leftOperand);

  AssignmentNode *assignmentLeftOperand = dynamic_cast<AssignmentNode *>(leftOperand);

  if (leftOperand->nodeType == nt_binaryExpression &&
      operatorPrecedence(binaryExpressionLeftOperand->op) < operatorPrecedence(token.value)) {
    // debug("Encountered superior operator in righthand binary expression...");
    Node *parentLeft = binaryExpressionLeftOperand->left;
    Node *childLeft = binaryExpressionLeftOperand->right;
    std::string parentOperator = binaryExpressionLeftOperand->op;

    BinaryExpressionNode *replacedParent = new BinaryExpressionNode();
    replacedParent->left = parentLeft;
    replacedParent->op = parentOperator;
    replacedParent->parent = node;

    BinaryExpressionNode *rightChild = new BinaryExpressionNode();
    rightChild->left = childLeft;
    rightChild->op = token.value;
    rightChild->parent = replacedParent;

    scopes.push_back(st_binaryOperator);
    replacedParent->right = rightChild;
    node->pushToExpressionList(currentScope, replacedParent);
    node = rightChild;

    return;
  } else if (leftOperand->nodeType == nt_assignment && assignmentLeftOperand != nullptr) {
    //
    //
    // FIXME: SAMMY! This is not properly handling operator precedence inside of assignment because it's a holdover from JS, which also does not properly handle operator precedence inside of assignment. Lol.
    //
    //
    // debug("Handling assignment left operand...");
    std::string parentVariable = assignmentLeftOperand->variable;
    Node *childLeft = assignmentLeftOperand->child;

    BinaryExpressionNode *binaryExpressionAssignmentChild =
        dynamic_cast<BinaryExpressionNode *>(childLeft);

    //
    //
    // FIXME: SAMMY! This is true when it's supposed to be true! Figure out what to do with it though.
    //
    //
    if (binaryExpressionAssignmentChild != nullptr &&
        (operatorPrecedence(binaryExpressionAssignmentChild->op) <
         operatorPrecedence(token.value))) {

      // debug("Encountered superior operator as child of assignment.");

      AssignmentNode *replacedParent = new AssignmentNode();
      replacedParent->parent = node;
      replacedParent->variable = parentVariable;

      Node *parentLeft = binaryExpressionAssignmentChild->left;
      Node *childLeft = binaryExpressionAssignmentChild->right;
      std::string parentOperator = binaryExpressionAssignmentChild->op;

      BinaryExpressionNode *replacedAssignmentChild = new BinaryExpressionNode();
      replacedAssignmentChild->left = parentLeft;
      replacedAssignmentChild->op = parentOperator;
      replacedAssignmentChild->parent = node;

      BinaryExpressionNode *rightChild = new BinaryExpressionNode();
      rightChild->left = childLeft;
      rightChild->op = token.value;
      rightChild->parent = replacedAssignmentChild;

      scopes.push_back(st_binaryOperator);
      replacedAssignmentChild->right = rightChild;
      replacedParent->child = replacedAssignmentChild;
      node->pushToExpressionList(currentScope, replacedParent);
      node = rightChild;

      return;
    } else {
      // debug("Handling inferior operator to other operator child of assignment");
      AssignmentNode *replacedParent = new AssignmentNode();
      replacedParent->parent = node;
      replacedParent->variable = parentVariable;

      BinaryExpressionNode *child = new BinaryExpressionNode();
      child->left = childLeft;
      child->op = token.value;
      child->parent = replacedParent;

      scopes.push_back(st_binaryOperator);
      replacedParent->child = child;
      node->pushToExpressionList(currentScope, replacedParent);
      node = child;

      return;
    }
  } else {
    BinaryExpressionNode *child = new BinaryExpressionNode();
    child->parent = node;
    child->left = leftOperand;
    child->op = token.value;
    node->pushToExpressionList(currentScope, child);
    node = child;

    return;
  }
}

} // namespace lydianlang
