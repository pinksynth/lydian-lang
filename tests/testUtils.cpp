#include <array>
#include <cstdio>
#include <cstring>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#include <fmt/core.h>

// Gets output from an arbitrary system command.
//   https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string getOutputFromSystemCommand(std::string strCmd) {
  const char *cmd = strCmd.c_str();
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

  if (!pipe)
    throw std::runtime_error("popen() failed!");

  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    result += buffer.data();

  return result;
}

std::string writeStringToTmpFile(std::string contents) {
  char tmpFileName[PATH_MAX];
  snprintf(tmpFileName, PATH_MAX - 1, "./%s.XXXXXX", "tmp");
  int fileDescriptor = mkstemp(tmpFileName);
  FILE *outFile = fdopen(fileDescriptor, "w");
  const char *contentsCStr = contents.c_str();
  write(fileDescriptor, contentsCStr, strlen(contentsCStr));
  fclose(outFile);
  std::string stringFileName(tmpFileName);
  return stringFileName;
}

std::vector<lydianlang::Token> tokenArrayFromJson(json jsonArray) {
  std::vector<lydianlang::Token> tokens = {};

  for (json::iterator item = jsonArray.begin(); item != jsonArray.end(); ++item)
    tokens.push_back(lydianlang::Token(*item));

  return tokens;
};

void compareTokens(std::vector<lydianlang::Token> expectedTokens,
                   std::vector<lydianlang::Token> receivedTokens) {
  unsigned expectedTokensIndex = 0;
  unsigned receivedTokensIndex = 0;
  unsigned expectedSize = expectedTokens.size();
  unsigned receivedSize = receivedTokens.size();

  while (expectedTokensIndex < expectedSize || receivedTokensIndex < receivedSize) {
    lydianlang::Token tokenA = expectedTokens[expectedTokensIndex];
    lydianlang::Token tokenB = receivedTokens[receivedTokensIndex];

    REQUIRE(tokenA == tokenB);

    if (expectedTokensIndex < expectedSize)
      ++expectedTokensIndex;

    if (receivedTokensIndex < receivedSize)
      ++receivedTokensIndex;

    if ((expectedTokensIndex == expectedSize && receivedTokensIndex < receivedSize)) {
      throw std::logic_error("Lexer produced too many tokens.");
    } else if (receivedTokensIndex == receivedSize && expectedTokensIndex < expectedSize) {
      throw std::logic_error("Lexer produced too few tokens.");
    }
  }
}

std::vector<lydianlang::Token> doTokenAssertions(std::filesystem::path currentFile) {
  std::ifstream inputFileStream(currentFile.parent_path() / "input.lydian");
  std::ostringstream inputFileStreamString;
  inputFileStreamString << inputFileStream.rdbuf();
  std::string inputString = inputFileStreamString.str();

  std::ifstream expectedTokensFileStream(currentFile.parent_path() / "expectedTokens.json");
  json expectedTokensJson = json::parse(expectedTokensFileStream);
  std::vector<lydianlang::Token> expectedTokens = tokenArrayFromJson(expectedTokensJson);

  lydianlang::Lexer lexer = lydianlang::Lexer();
  std::vector<lydianlang::Token> receivedTokens = lexer.lex(inputString);

  compareTokens(expectedTokens, receivedTokens);

  return receivedTokens;
}

void doASTAssertions(std::filesystem::path currentFile,
                     std::vector<lydianlang::Token> receivedTokens) {
  std::filesystem::path expectedASTPath(currentFile.parent_path() / "expectedAST.json");

  if (!std::filesystem::exists(expectedASTPath)) {
    lydianlang::alert("WARNING: Could not find " + expectedASTPath.generic_string());
  } else {

    std::ifstream expectedASTFileStream(expectedASTPath);
    std::string expectedASTJson = json::parse(expectedASTFileStream).dump(2);

    lydianlang::LydianAST ast = lydianlang::LydianAST();
    ast.fromTokens(receivedTokens);
    std::string receivedASTJson = ast.jsonAST.dump(2);

    if (expectedASTJson != receivedASTJson) {
      std::string tmpFilename1 = writeStringToTmpFile(expectedASTJson);
      std::string tmpFilename2 = writeStringToTmpFile(receivedASTJson);

      char diffOutputFilename[PATH_MAX];
      snprintf(diffOutputFilename, PATH_MAX - 1, "./%s.XXXXXX", "tmp");
      int diffOutputFd = mkstemp(diffOutputFilename);
      FILE *diffOut = fdopen(diffOutputFd, "w");

      lydianlang::alert("AST is invalid for\n\n  " + currentFile.generic_string());
      std::cout << getOutputFromSystemCommand(
                       fmt::format("diff -u --color=always {} {}", tmpFilename1, tmpFilename2))
                << std::endl;
      fclose(diffOut);
      remove(tmpFilename1.c_str());
      remove(tmpFilename2.c_str());

      throw std::logic_error("Test failed AST assertion.");
    };
  }
}

// Makes assertions based on three files per test case. The test case's `input.lydian` is the Lydian Lang input. The Lexer produces tokens and those tokens are compared with `expectedTokens.json`. Then the tokens are fed to the AST, which is expected to look like `expectedAST.json`.
void doAssertions(std::filesystem::path currentFile) {
  std::vector<lydianlang::Token> receivedTokens = doTokenAssertions(currentFile);
  doASTAssertions(currentFile, receivedTokens);
}
