#!/bin/bash

set -e

if [ -z "$CXX" ]; then
    CXX=clang++
fi

while getopts "blc" flag; do
    case "$flag" in
    b) BENCH="-DCATCH_CONFIG_ENABLE_BENCHMARKING" ;;
    l) USE_LAST_FILE=true ;;
    c) COVERAGE="-fprofile-instr-generate -fcoverage-mapping" ;;
    esac
done

if [ "$USE_LAST_FILE" == true ]; then
    files=$(ls -t src/*.cpp | head -1)
elif [ $(($# - $OPTIND + 1)) -gt 0 ]; then
    files=${@:$OPTIND:$(($# - $OPTIND + 1))}
else
    files=src/*.cpp
fi

$CXX --std=c++14 -g -Wall $COVERAGE $BENCH -I. main.cpp $files -o a.out
if [ -z "$COVERAGE" ]; then
    ./a.out
else
    LLVM_PROFILE_FILE=a.profraw ./a.out
    llvm-profdata merge -sparse a.profraw -o a.profdata
    llvm-cov show ./a.out -instr-profile=a.profdata >coverage.txt
    llvm-cov report ./a.out -instr-profile=a.profdata
fi
