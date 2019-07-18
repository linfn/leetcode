#!/bin/bash

set -e

if [ -z $CXX ]; then
    CXX=clang++
fi

if [ $# -gt 0 ]; then
    files=$*
else
    files=src/*.cpp
fi

$CXX --std=c++14 -g -o a.out -I. main.cpp $files
./a.out
