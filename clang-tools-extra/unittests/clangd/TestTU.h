//===--- TestTU.h - Scratch source files for testing ------------*- C++-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Many tests for indexing, code completion etc are most naturally expressed
// using code examples.
// TestTU lets test define these examples in a common way without dealing with
// the mechanics of VFS and compiler interactions, and then easily grab the
// AST, particular symbols, etc.
//
//===---------------------------------------------------------------------===//
#ifndef LLVM_CLANG_TOOLS_EXTRA_UNITTESTS_CLANGD_TESTTU_H
#define LLVM_CLANG_TOOLS_EXTRA_UNITTESTS_CLANGD_TESTTU_H
#include "ClangdUnit.h"
#include "index/Index.h"
#include "gtest/gtest.h"

namespace clang {
namespace clangd {

struct TestTU {
  static TestTU withCode(llvm::StringRef Code) {
    TestTU TU;
    TU.Code = Code;
    return TU;
  }

  static TestTU withHeaderCode(llvm::StringRef HeaderCode) {
    TestTU TU;
    TU.HeaderCode = HeaderCode;
    return TU;
  }

  // The code to be compiled.
  std::string Code;
  std::string Filename = "TestTU.cpp";

  // Define contents of a header to be included by TestTU.cpp.
  std::string HeaderCode;
  std::string HeaderFilename = "TestTU.h";

  ParsedAST build() const;
  SymbolSlab headerSymbols() const;
  std::unique_ptr<SymbolIndex> index() const;
};

// Look up an index symbol by qualified name, which must be unique.
const Symbol &findSymbol(const SymbolSlab &, llvm::StringRef QName);
// Look up an AST symbol by qualified name, which must be unique and top-level.
const NamedDecl &findDecl(ParsedAST &AST, llvm::StringRef QName);

} // namespace clangd
} // namespace clang
#endif
