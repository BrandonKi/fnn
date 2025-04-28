#include "Factorio/FactorioDialect.h"
#include "Factorio/FactorioOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Dialect/Torch/IR/TorchDialect.h"

using namespace mlir;

namespace {
struct LowerTorchToFactorioPass
    : public PassWrapper<LowerTorchToFactorioPass, OperationPass<ModuleOp>> {
    void runOnOperation() override {
        ModuleOp module = getOperation();
            module.walk([&](torch::TorchDialect::AddOp op) {
                OpBuilder builder(op);
                auto lhs = op.getOperand(0);
                auto rhs = op.getOperand(1);
                builder.create<factorio::AddOp>(op.getLoc(), op.getType(), lhs, rhs);
                op.erase();
            });
    }
};
} // namespace

std::unique_ptr<Pass> createLowerTorchToFactorioPass() {
    return std::make_unique<LowerTorchToFactorioPass>();
}

// Register the pass
static PassRegistration<LowerTorchToFactorioPass> pass("lower-torch-to-factorio", "Lower Torch ops to Factorio dialect");
