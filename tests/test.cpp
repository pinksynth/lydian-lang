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
#include "../src/Token.cpp"
#include "../src/TokenType.cpp"
#include "./testUtils.cpp"

#include "./cases/booleans-1/test.cpp"
#include "./cases/small-file-1/test.cpp"
