#!/bin/bash

set -e

while getopts "blc" flag; do
    case "$flag" in
    b) BENCH="-DCATCH_CONFIG_ENABLE_BENCHMARKING" ;;
    l) USE_LAST_FILE=true ;;
    c) COVERAGE="-fprofile-instr-generate -fcoverage-mapping" ;;
    esac
done

if [ "$USE_LAST_FILE" == true ]; then
    files=$(ls -t src/*.cpp | head -1)
    echo "test file: $files"
elif [ $(($# - $OPTIND + 1)) -gt 0 ]; then
    files=${@:$OPTIND:$(($# - $OPTIND + 1))}
else
    files=src/*.cpp
fi

clang++ --std=c++14 -g -Wall $COVERAGE $BENCH -I include main.cpp $files -o a.out

if [ -z "$COVERAGE" ]; then
    ./a.out
else
    LLVM_PROFILE_FILE=a.profraw ./a.out
    llvm-profdata merge -sparse a.profraw -o a.profdata
    llvm-cov show ./a.out -instr-profile=a.profdata >coverage.txt
    llvm-cov report ./a.out -instr-profile=a.profdata
fi
