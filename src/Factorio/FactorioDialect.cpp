#include "Factorio/FactorioDialect.h"
#include "Factorio/FactorioOps.h"

#include "mlir/IR/Builders.h"
#include "mlir/IR/DialectImplementation.h"

using namespace mlir;
using namespace factorio;

#include "Factorio/FactorioOpsDialect.cpp.inc"

void FactorioDialect::initialize() {
    addOperations<
#define GET_OP_LIST
#include "Factorio/FactorioOps.cpp.inc"
    >();
}
