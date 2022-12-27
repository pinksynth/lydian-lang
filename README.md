# sammy-lang-cpp

An attempt to implement the sammy-lang language in C++ using LLVM.

## Building

Compile with `g++`. This project uses C++11 features, so you may need to add the `-std=c++11` flag:

```
g++ src/main.cpp -std=c++11 -o sammy.out && ./sammy.out
```
