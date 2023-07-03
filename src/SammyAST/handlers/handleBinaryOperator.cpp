#include "../Node.cpp"
#include "../nodeTypes/AssignmentNode/AssignmentNode.cpp"
#include "../nodeTypes/BinaryExpressionNode/BinaryExpressionNode.cpp"

namespace sammylang {

void SammyAST::handleBinaryOperator() {
  debug("Handling binary operator...");
  ScopeType prevScope = scopes.back();
  currentExpressionList = node->getCurrentExpressionList(prevScope);
  scopes.push_back(st_binaryOperator);

  // When we encounter a binary operator, it means that the previous sibling must be treated not as its own statement, but rather an operand of this operator.
  Node *leftOperand = currentExpressionList.back();
  currentExpressionList.pop_back();
  node->popCurrentExpressionList();

  // Here we do some swapping to handle operator precedence.
  // That is, we check to see if we found 2 + 3 * 4.
  // The algorithm wants this to be ((2 + 3) * 4).
  // So we have to tell it to be (2 + (3 * 4)).
  // In order to do this, we take the left operand ((2 + 3)) and check if it is a binary expression with a lower-priority operator. If it is, then we instead replace the whole node with its lefthand operand (2).
  BinaryExpressionNode *binaryExpressionLeftOperand =
      dynamic_cast<BinaryExpressionNode *>(leftOperand);

  AssignmentNode *assignmentLeftOperand = dynamic_cast<AssignmentNode *>(leftOperand);

  //
  //
  // FIXME: This ain't working. Operator precedence is being broken by the current input in main.cpp.
  //
  //
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
    node->pushToExpressionList(replacedParent);
    node = rightChild;

    return;
  } else if (leftOperand->nodeType == nt_assignment && assignmentLeftOperand != nullptr) {
    debug("Handling assignment left operand...");
    std::string parentVariable = assignmentLeftOperand->variable;
    Node *childLeft = assignmentLeftOperand->child;

    AssignmentNode *replacedParent = new AssignmentNode();
    replacedParent->parent = node;
    replacedParent->variable = parentVariable;

    BinaryExpressionNode *rightChild = new BinaryExpressionNode();
    rightChild->left = childLeft;
    rightChild->op = token.value;
    rightChild->parent = replacedParent;

    scopes.push_back(st_binaryOperator);
    replacedParent->child = rightChild;
    debug("replacedParent->inspectString()");
    debug(replacedParent->inspectString());
    node->pushToExpressionList(replacedParent);
    node = rightChild;
    /*
      const parentVariable = leftOperand.variable
      const childLeft = leftOperand.children[0]

      const replacedParent = {
        variable: parentVariable,
        parent: node,
        type: nt.ASSIGNMENT,
        lineNumberStart: leftOperand.lineNumberStart,
        columnNumberStart: leftOperand.columnNumberStart,
      }
      const rightChild = {
        left: childLeft,
        operator: token.value,
        parent: replacedParent,
        type: nt.BINARY_EXPR,
        lineNumberStart: token.lineNumberStart,
        columnNumberStart: token.columnNumberStart,
      }

      scopes.push(st.BINARY_OPERATOR)
      replacedParent.children = [rightChild]
      pushToExpressionList(replacedParent)

      setNode(rightChild)

      */

  } else {

    // If the operator is the righthand side of an assignment, we do essentially the same thing as the ("foo = 3 * 4" instead of "2 + 3 * 4") scenario, except that the structure of the replaced parent node is slightly different (assignments are like binary operators, but with slightly different rules).
    // } else if (leftOperand.type === nt.ASSIGNMENT) {
    //   handleOperatorAsRightSideOfAssignment({
    //     leftOperand,
    //     node,
    //     pushToExpressionList,
    //     scopes,
    //     setNode,
    //     token,
    //   })

    //   return
    // } else {
    // If we encountered neither an assignment (foo = 3 * 4) nor an operator precedence conflict (2 + 3 * 4), then simply treat the previous sibling node as our left operand and proceed.
    BinaryExpressionNode *child = new BinaryExpressionNode();
    child->parent = node;
    child->left = leftOperand;
    child->op = token.value;
    node->pushToExpressionList(child);
    node = child;
  }
}

} // namespace sammylang

/*
const nt = require("./nodeTypes")
const operatorPrecedence = require("./operatorPrecedence")
const st = require("./scopeTypes")

const handleSuperiorOperator = ({
  leftOperand,
  node,
  pushToExpressionList,
  scopes,
  setNode,
  token,
}) => {
  const parentLeft = leftOperand.left
  const childLeft = leftOperand.right
  const parentOperator = leftOperand.operator

  const replacedParent = {
    left: parentLeft,
    operator: parentOperator,
    parent: node,
    type: nt.BINARY_EXPR,
    lineNumberStart: leftOperand.lineNumberStart,
    columnNumberStart: leftOperand.columnNumberStart,
  }
  const rightChild = {
    left: childLeft,
    operator: token.value,
    parent: replacedParent,
    type: nt.BINARY_EXPR,
    lineNumberStart: token.lineNumberStart,
    columnNumberStart: token.columnNumberStart,
  }

  scopes.push(st.BINARY_OPERATOR)
  replacedParent.right = rightChild
  pushToExpressionList(replacedParent)

  setNode(rightChild)
}

const handleOperatorAsRightSideOfAssignment = ({
  leftOperand,
  node,
  pushToExpressionList,
  scopes,
  setNode,
  token,
}) => {
  const parentVariable = leftOperand.variable
  const childLeft = leftOperand.children[0]

  const replacedParent = {
    variable: parentVariable,
    parent: node,
    type: nt.ASSIGNMENT,
    lineNumberStart: leftOperand.lineNumberStart,
    columnNumberStart: leftOperand.columnNumberStart,
  }
  const rightChild = {
    left: childLeft,
    operator: token.value,
    parent: replacedParent,
    type: nt.BINARY_EXPR,
    lineNumberStart: token.lineNumberStart,
    columnNumberStart: token.columnNumberStart,
  }

  scopes.push(st.BINARY_OPERATOR)
  replacedParent.children = [rightChild]
  pushToExpressionList(replacedParent)

  setNode(rightChild)
}

const handleBinaryOperator = ({
  currentExpressionList,
  node,
  pushToExpressionList,
  scopes,
  setNode,
  token,
}) => {
  scopes.push(st.BINARY_OPERATOR)

  // When we encounter a binary operator, it means that the previous sibling must be treated not as its own statement, but rather an operand of this operator.
  const leftOperand = currentExpressionList.pop()

  // Here we do some swapping to handle operator precedence.
  // That is, we check to see if we found 2 + 3 * 4.
  // The algorithm wants this to be ((2 + 3) * 4).
  // So we have to tell it to be (2 + (3 * 4)).
  // In order to do this, we take the left operand ((2 + 3)) and check if it is a binary expression with a lower-priority operator. If it is, then we instead replace the whole node with its lefthand operand (2).
  if (
    leftOperand.type === nt.BINARY_EXPR &&
    operatorPrecedence(leftOperand.operator) < operatorPrecedence(token.value)
  ) {
    handleSuperiorOperator({
      leftOperand,
      node,
      pushToExpressionList,
      scopes,
      setNode,
      token,
    })

    return
    // If the operator is the righthand side of an assignment, we do essentially the same thing as the ("foo = 3 * 4" instead of "2 + 3 * 4") scenario, except that the structure of the replaced parent node is slightly different (assignments are like binary operators, but with slightly different rules).
  } else if (leftOperand.type === nt.ASSIGNMENT) {
    handleOperatorAsRightSideOfAssignment({
      leftOperand,
      node,
      pushToExpressionList,
      scopes,
      setNode,
      token,
    })

    return
  } else {
    // If we encountered neither an assignment (foo = 3 * 4) nor an operator precedence conflict (2 + 3 * 4), then simply treat the previous sibling node as our left operand and proceed.
    const child = {
      left: leftOperand,
      operator: token.value,
      parent: node,
      type: nt.BINARY_EXPR,
      lineNumberStart: token.lineNumberStart,
      columnNumberStart: token.columnNumberStart,
    }
    pushToExpressionList(child)
    setNode(child)

    return
  }
}

module.exports = handleBinaryOperator
*/