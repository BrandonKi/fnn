cmake_minimum_required(VERSION 3.13)

project(FactorioDialects)

find_package(MLIR REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard")

include_directories(${MLIR_INCLUDE_DIRS})
add_definitions(${MLIR_DEFINITIONS})

# Dialect and ops
add_mlir_dialect(Factorio factorio)
add_mlir_doc(FactorioOps Factorio Dialects/ -gen-dialect-doc)

# Libraries
add_mlir_library(FactorioDialect
  lib/Factorio/FactorioDialect.cpp
  lib/Factorio/FactorioOps.cpp

  DEPENDS
  FactorioOpsIncGen
)

# Pass
add_mlir_library(LowerTorchToFactorio
  tools/LowerTorchToFactorioPass.cpp

  LINK_LIBS PUBLIC
  FactorioDialect
  MLIRIR
  MLIRPass
  MLIRTorch
)

# Tools
add_executable(lower-torch-to-factorio
  tools/LowerTorchToFactorioPass.cpp
)

target_link_libraries(lower-torch-to-factorio PRIVATE
  LowerTorchToFactorio
  FactorioDialect
  MLIRIR
  MLIRPass
  MLIRTorch
)
