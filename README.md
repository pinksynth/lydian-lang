# sammy-lang-cpp

An attempt to implement the sammy-lang language in C++ using LLVM.

## Building

This project uses CMake and Conan. To build, first make sure that `conan` and `cmake` are installed.

1. Make the `build` folder if it does not exist, and enter it (this folder is ignored by git):
   ```sh
   mkdir build; cd build
   ```
2. Install dependencies:
   ```sh
   conan install ..
   ```
3. Run `cmake`:
   ```sh
   cmake ..
   ```
4. Run `make`:
   ```sh
   make
   ```
5. You can now run the built executable:
   ```sh
   DEBUG=true bin/sammy-lang
   ```

To enable debugging, export the DEBUG variable in your shell before compiling:

```sh
export DEBUG=true; g++ src/main.cpp -std=c++11 -o sammy.out && ./sammy.out
```

### Note about compiler settings

I've only built this on my MacBook using a generic `apple-clang` Conan profile:

```
# ~/.conan/profiles/default

[settings]
os=Macos
os_build=Macos
arch=x86_64
arch_build=x86_64
compiler=apple-clang
compiler.version=14
compiler.libcxx=libc++
build_type=Release
[options]
[build_requires]
[env]
```
