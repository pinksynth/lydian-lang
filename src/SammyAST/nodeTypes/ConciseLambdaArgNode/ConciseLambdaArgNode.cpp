#include "./ConciseLambdaArgNode.h"

std::string ConciseLambdaArgNode::inspectString(int pad) {
  return "Concise λ Arg Node: " + std::to_string(id);
};

json ConciseLambdaArgNode::toJson() {
  json lambdaJson = {{"nodeType", nt_conciseLambdaArgument}, {"id", id}};
  return lambdaJson;
};