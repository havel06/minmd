#!/bin/bash

clang-tidy src/* -p build/ -checks=*,-llvmlibc-restrict-system-libc-headers,-modernize-use-trailing-return-type,-llvm-header-guard,-llvmlibc-callee-namespace,-llvmlibc-implementation-in-namespace,-llvmlibc-restrict-system-libc-headers,-fuchsia-default-arguments-calls
