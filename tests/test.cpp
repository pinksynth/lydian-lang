// FIXME: These imports are probably unhygienic. I should really find somebody who uses this language and ask them.
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <vector>

#include "../src/utils.cpp"

#include "../src/InterpolationContextStack/InterpolationContextStack.cpp"
#include "../src/Lexer/Lexer.cpp"
#include "../src/LydianAST/LydianAST.cpp"
#include "../src/Token.cpp"
#include "../src/TokenType.cpp"
#include "./testUtils.cpp"

/*
	Import test cases. Each case directory has a few files:
		* `test.cpp` - The entrypoint for the test case. May perform any assertions about the language feature. If `doAssertions` is called, the following files should also be present.
		* `input.lydian` - The input lydianlang file.
		* `expectedTokens.json` The expected lexer tokens for the given input.
		* `expectedAST.json` The expected AST for the given input.
*/

#include "./cases/assignment-1/test.cpp"
#include "./cases/big-file-1/test.cpp"
#include "./cases/booleans-1/test.cpp"
#include "./cases/comments-1/test.cpp"
#include "./cases/function-calls-1/test.cpp"
#include "./cases/function-definitions-1/test.cpp"
#include "./cases/generic-expressions-1/test.cpp"
#include "./cases/if-else-1/test.cpp"
#include "./cases/lambdas-1/test.cpp"
#include "./cases/lists-1/test.cpp"
#include "./cases/numbers-1/test.cpp"
#include "./cases/operator-precedence-big-1/test.cpp"
#include "./cases/operator-precedence-small-1/test.cpp"
#include "./cases/small-file-1/test.cpp"
#include "./cases/string-interpolation-1/test.cpp"
#include "./cases/variables-1/test.cpp"
