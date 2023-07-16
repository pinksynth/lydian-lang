# lydian-lang

An attempt to implement the lydian-lang language in C++ using LLVM.

## Building

This project uses CMake. To build, first make sure that `cmake` is installed. Then run `scripts/initial-build.sh`.

Alternatively, you can follow the steps below:

1. Make the `build` folder if it does not exist, and enter it (this folder is ignored by git):
   ```sh
   mkdir build; cd build
   ```
   **NOTE: All steps below must be run in the `build` folder.**
2. Run `cmake`:
   ```sh
   cmake ..
   ```
3. Run `make`:
   ```sh
   make
   ```
4. You can now run the built executables `lydian-lang` and `tests`:

   ```sh
   bin/lydian-lang
   bin/tests

   # With debug output
   DEBUG=true bin/lydian-lang
   DEBUG=true bin/tests
   ```

## Testing

Follow the same steps as above, but instead of running the `lydian-lang` executable, run the `tests` executable.

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
