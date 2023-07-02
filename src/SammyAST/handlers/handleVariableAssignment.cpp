#include "../Node.cpp"
#include "../nodeTypes/AssignmentNode/AssignmentNode.cpp"

namespace sammylang {
void SammyAST::handleVariableAssignment() {
  ScopeType currentScope = scopes.back();
  if (!inList(currentScope, st_validAssignmentScopes)) {
    throw std::logic_error("Unexpected assigment.");
  }

  scopes.push_back(st_assignment);
  AssignmentNode *child = new AssignmentNode();
  child->parent = node;
  child->variable = token.value;

  node->pushToExpressionList(child);
  node = child;
  consumeExtra();
  /*
		if (
			![
				st.ENUM_DEFINITION,
				st.FUNCTION_DEC_BODY,
				st.IF_BODY,
				st.LAMBDA_BODY,
				st.ROOT,
				st.STRING_INTERPOLATION,
				st.STRUCT_DEFINITION,
			].includes(currentScope)
		) {
			// TODO: Implement test
			throw new Error(
				`Unexpected assigment on line ${token.lineNumberStart}: ${token.value}`
			)
		}

		scopes.push(st.ASSIGNMENT)
		const child = {
			children: [],
			parent: node,
			type: nt.ASSIGNMENT,
			variable: token.value,
			weak: false,
			lineNumberStart: token.lineNumberStart,
			columnNumberStart: token.columnNumberStart,
		}
		pushToExpressionList(child)
		setNode(child)

		// For normal var assignments, we have consumed both the identifier and the operator, so we'll manually increment the tokens by an extra 1.
		consumeExtra()
	*/
}
} // namespace sammylang
