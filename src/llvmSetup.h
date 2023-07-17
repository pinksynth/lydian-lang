// NOTE: The linker failures in this file could be because the appropriate compiler flags are not being set. LLVM suggests this:
// # Compile
// clang++ -g toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core orcjit native` -O3 -o toy
// # Run
// ./toy

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#pragma once

namespace lydianlang {

static std::unique_ptr<llvm::LLVMContext> TheContext;
static std::unique_ptr<llvm::Module> TheModule;
static std::unique_ptr<llvm::IRBuilder<>> Builder;
static std::map<std::string, llvm::Value *> NamedValues;

// static std::unique_ptr<llvm::orc::KaleidoscopeJIT> TheJIT;

// static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

void setupLLVM() {
  // See the LLVM tutorial for reference:
  //   https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl04.html

  // Open a new context and module.
  TheContext = std::make_unique<llvm::LLVMContext>();
  TheModule = std::make_unique<llvm::Module>("Sammy's JIT", *TheContext);

  // FIXME: JIT stuff fails at linking time on my architecture for some reason. Gonna have to skip fancy JIT-ness for the time being.
  // TheModule->setDataLayout(TheJIT->getDataLayout());
  // // Set up JIT (uses same implementation as Kaleidoscope)
  // llvm::InitializeNativeTarget();
  // llvm::InitializeNativeTargetAsmPrinter();
  // llvm::InitializeNativeTargetAsmParser();

  // FIXME: FunctionPassManager stuff fails at linking time on my architecture for some reason. Gonna have to skip optimizations for the time being.
  // // Create a new pass manager attached to it.
  // TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());

  // // Do simple "peephole" optimizations and bit-twiddling optzns.
  // TheFPM->add(llvm::createInstructionCombiningPass());
  // // Reassociate expressions.
  // TheFPM->add(llvm::createReassociatePass());
  // // Eliminate Common SubExpressions.
  // TheFPM->add(llvm::createGVNPass());
  // // Simplify the control flow graph (deleting unreachable blocks, etc).
  // TheFPM->add(llvm::createCFGSimplificationPass());

  // TheFPM->doInitialization();

  // Create a new builder for the module.
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
};

} // namespace lydianlang