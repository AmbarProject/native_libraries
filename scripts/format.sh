#!/bin/bash

# Format C++ code using clang-format

find src include -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i -style=file

echo "Code formatted successfully"