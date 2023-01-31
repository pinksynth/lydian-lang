# sammy-lang-cpp

An attempt to implement the sammy-lang language in C++ using LLVM.

## Building

This project uses CMake and Conan. To build, first make sure that `conan` and `cmake` are installed. Then run `scripts/initial-build.sh`.

Alternatively, you can follow the steps below:

1. Make the `build` folder if it does not exist, and enter it (this folder is ignored by git):
   ```sh
   mkdir build; cd build
   ```
   **NOTE: All steps below must be run in the `build` folder.**
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
5. You can now run the built executables `sammy-lang` and `tests`:

   ```sh
   bin/sammy-lang
   bin/tests

   # With debug output
   DEBUG=true bin/sammy-lang
   DEBUG=true bin/tests
   ```

## Testing

Follow the same steps as above, but instead of running the `sammy-lang` executable, run the `tests` executable.

## Note about compiler settings

CMake should enable this project to be built on various platforms, but I've only built it on my MacBook using a generic `apple-clang` Conan profile:

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

## Debugging and building in VSCode

To debug in VSCode, follow the build steps and install all the recommended Workspace extensions. The [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extensions allow you to use CMake's build tasks from VSCode (if you're into that), and the [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb) extension is used to Then you should be able to use VSCode's debug tools "automagically".
