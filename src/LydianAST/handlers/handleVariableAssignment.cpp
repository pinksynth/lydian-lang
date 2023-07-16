#include "../Node.cpp"
#include "../nodeTypes/AssignmentNode/AssignmentNode.cpp"

namespace lydianlang {
void LydianAST::handleVariableAssignment() {
  ScopeType currentScope = scopes.back();
  if (!inList(currentScope, st_validAssignmentScopes)) {
    throw std::logic_error("Unexpected assigment.");
  }

  scopes.push_back(st_assignment);
  AssignmentNode *child = new AssignmentNode();
  child->parent = node;
  child->variable = token.value;

  node->pushToExpressionList(currentScope, child);
  node = child;
  consumeExtra();
}

} // namespace lydianlang
