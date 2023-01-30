TEST_CASE("Booleans 1") {
  print("Testing: Booleans 1");

  std::ifstream file("../tests/cases/booleans-1/expectedTokens.json");
  json data = json::parse(file);
  std::vector<Token> expectedTokens = tokenArrayFromJson(data);

  std::ifstream inputFileStream("../tests/cases/booleans-1/input.sammy");
  std::ostringstream inputFileStreamString;
  inputFileStreamString << inputFileStream.rdbuf();
  std::string inputString = inputFileStreamString.str();

  std::cout << "File Contents: " << inputString << std::endl;

  Lexer lexer = Lexer();
  std::vector<Token> received = lexer.lex(inputString);

  compareTokens(expectedTokens, received);
}
