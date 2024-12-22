#!/bin/bash

set -Eeuo pipefail

mkdir -p build
cd build
cmake ..
make
cd ..
./build/tests
