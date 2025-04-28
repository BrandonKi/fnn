include "mlir/IR/OpBase.td"

def Factorio_Dialect : Dialect {
    let name = "factorio";
}

def Factorio_AddOp : Op<Factorio_Dialect, "add", [Commutative]> {
    let summary = "Addition op for Factorio dialect";
    let arguments = (ins TensorOf<[F32]>:$lhs, TensorOf<[F32]>:$rhs);
    let results = (outs TensorOf<[F32]>:$result);
}
