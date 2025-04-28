import torch
import torch_mlir

class MyModel(torch.nn.Module):
    def forward(self, x):
        return x + 1

model = MyModel()
model.eval()

input = torch.randn(1, 3)

mlir_module = torch_mlir.compile(
    model,
    (input,),
    output_type=torch_mlir.OutputType.TORCH
)

with open("../test/model.mlir", "w") as f:
    f.write(str(mlir_module))
