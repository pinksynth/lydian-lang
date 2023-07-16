# lydian-lang

An attempt to implement the lydian-lang language in C++ using LLVM.

## Building

This project uses CMake. To build, first make sure that `cmake` and `llvm` are installed:

- [Install `cmake`](https://cmake.org/install/)
- [Install `llvm`](https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm)

Then run `scripts/initial-build.sh`.

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
4. You can now run the built executables `lydian-lang`, `repl`, and `tests`:

   ```sh
   bin/lydian-lang
   bin/repl
   bin/tests

   # With debug output
   DEBUG=true bin/lydian-lang
   DEBUG=true bin/tests
   ```

Because the language is a work in progress, the REPL doesn't actually "evaluate" expressions, but it does produce an AST:

```
Welcome to LydianLang


𝐋1> fn multiply(a b) { a * b }
fn multiply(a b) { a * b }
JSON Output from AST:
{
  "children": [
    {
      "arguments": [
        {
          "nodeType": "nt_identifier",
          "value": "a"
        },
        {
          "nodeType": "nt_identifier",
          "value": "b"
        }
      ],
      "children": [
        {
          "left": {
            "nodeType": "nt_identifier",
            "value": "a"
          },
          "nodeType": "nt_binaryExpression",
          "operator": "*",
          "right": {
            "nodeType": "nt_identifier",
            "value": "b"
          }
        }
      ],
      "nodeType": "nt_functionDeclaration"
    }
  ],
  "nodeType": "nt_root"
}

𝐋2>
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
