cmake_minimum_required(VERSION 3.14)

project(sammy-lang VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

#
# JSON
#
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

#
# String formatting
#
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 7.0.0
)
FetchContent_MakeAvailable(fmt)

add_executable(sammy-lang src/main.cpp)
target_link_libraries(
  sammy-lang
  ${llvm_libs}
  fmt
  nlohmann_json::nlohmann_json
)

add_executable(repl src/repl.cpp)
target_link_libraries(
  repl
  ${llvm_libs}
  fmt
  nlohmann_json::nlohmann_json
)

#
# Testing
#
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)
add_executable(tests tests/test.cpp)
target_link_libraries(
  tests
  PRIVATE
  ${llvm_libs}
  Catch2::Catch2WithMain
  fmt
  nlohmann_json::nlohmann_json
)
