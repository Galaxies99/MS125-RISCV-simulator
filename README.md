# RISCV-Simulator
这是一个同时支持串行和并行的 RISCV 模拟器。

默认为并行，将 main.cpp 中的 Pararrel 修改为 Serial 即可变为串行。

利用 lock 进行对于跳转指令处理，即碰到访问待修改的值即停下整个过程。

Update 2019.7.8：

利用 Forwarding 处理 Data Hazard，即处理后面的指令后需要向前更新已经取出的寄存器的值。



