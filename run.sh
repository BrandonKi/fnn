#!/bin/bash

set -e

echo "=== Step 1: Clone and build LLVM + MLIR ==="

# Clone if not already cloned
if [ ! -d "llvm-project" ]; then
    git clone https://github.com/llvm/llvm-project.git
fi

cd llvm-project

# Build LLVM + MLIR
mkdir -p build
cd build

cmake -G Ninja ../llvm \
  -DLLVM_ENABLE_PROJECTS="mlir" \
  -DLLVM_TARGETS_TO_BUILD="host" \
  -DCMAKE_BUILD_TYPE=Release \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DCMAKE_INSTALL_PREFIX=$HOME/llvm-install

ninja
ninja install

cd ../..

echo "=== Step 2: Configure and build pytorch-to-custom-mlir ==="

# Make sure we are at the root of your repo
# (Assumes this script is at the root of your repo)
mkdir -p build
cd build

cmake .. \
  -DMLIR_DIR=$HOME/llvm-install/lib/cmake/mlir \
  -DLLVM_DIR=$HOME/llvm_
