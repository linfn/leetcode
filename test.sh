#!/bin/bash

set -e

if [ -z $CXX ]; then
    CXX=clang++
fi

while getopts "b" flag; do
    case "$flag" in
    b) BENCH="-DCATCH_CONFIG_ENABLE_BENCHMARKING" ;;
    esac
done

if [ $(($# - $OPTIND + 1)) -gt 0 ]; then
    files=${@:$OPTIND:$(($# - $OPTIND + 1))}
else
    files=src/*.cpp
fi

$CXX --std=c++14 -g -o a.out $BENCH -I. main.cpp $files
./a.out
