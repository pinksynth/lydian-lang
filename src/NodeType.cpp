#pragma once

namespace sammylang {

enum NodeType {
  nt_binaryExpression,
  nt_conciseLambdaArgument,
  nt_identifier,
  nt_list,
  nt_literalBoolean,
  nt_literalNumber,
  nt_nil,
  nt_root
};

}