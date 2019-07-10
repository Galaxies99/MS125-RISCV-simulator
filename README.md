# RISCV-Simulator
这是一个同时支持串行和并行的 RISCV 模拟器。

默认为并行，将 main.cpp 中的 Pararrel 修改为 Serial 即可变为串行。

### v1.0

update time: 2019.7.4

实现了串行处理的功能，即一个命令执行后再执行下一个命令。

利用的是分 stage 执行，即每个 stage 封装一个 class，每次执行 go() 以及 pass() 来执行过程和传递结果。

在调试的过程中，发现了如下问题：

1. 寄存器中0的值不能被改变，且访问时始终返回0；
2. 最后返回的是寄存器中的值，而不是内存的值。

### v1.1 (trash)

update time: 2019.7.8

因为某些原因写了一个分指令类型的串行程序，效率并没有想象中的好，于是扔掉了…

### v2.0

update time: 2019.7.5

实现了并行处理的功能，即在可能出现 data hazard 和 control hazard 的时候，全部利用 lock() 对相应寄存器进行暂时锁定，以解决问题。

因为运行过于缓慢，此版本完成后转而写 v1.1 版本。

### v2.1

update time: 2019.7.8

v1.1 版本运行仍然缓慢，于是发现开 -O2 之后会快很多，因此将 v2.0 版本进行了 O2 优化。

### v3.0

update time: 2019.7.8

利用 Forwarding 处理了 Data Hazard，即增加 MA -> EX, EX -> ID, MA -> ID 的信息传输路线。

具体可见 forward.hpp 中的三个 Forward 函数。

### v3.1

update time: 2019.7.9

进行了小优化，对于JAL指令不再进行lock等待而直接跳转。

### v4.0 (trash)

update time: 2019.7.9

一个错误的版本，忽略…

### v5.0

update time: 2019.7.9

加入了分支预测，对于每个指令记录下前面若干次访问的结果，从而预测是跳转还是不跳转，预测失败需要清空前面指令的信息。

该版本分支预测全部跳转。

### v5.1

update time: 2019.7.9

该版本分支预测为采取前面所有指令的两种结果取 max 的一个结果。 

### v5.2

update time: 2019.7.9

该版本分支预测为采取前 10 条指令的两种结果取 max 的一个结果。

### v5.3

update time: 2019.7.10

对于一部分分支预测进行了加权。目前结果为：（仅摘取部分分支预测工作量大的数据）：

1. basicopt1：128895 / 155139  Accuracy 83.0836%
2. bulgarian: 57500 / 71493 Accuracy: 80.4275%
3. hanoi: 12839 / 17457 Accuracy: 73.5464%
4. magic: 40873 / 67869 Accuracy: 60.2234%
5. pi: 32374472 / 39956380 Accuracy: 81.0245%
6. qsort: 165102 / 200045 Accuracy: 82.5234%
7. queens: 53405 / 77116 Accuracy: 69.2528%
8. superloop: 376805 / 435027 Accuracy: 86.6165%
9. tak: 42972 / 60639 Accuracy: 70.8653%

### v5.4

update time: 2019.7.10

加入搜索循环节来分支预测

仅搜索长度为2、3且循环超过5次。

1. basicopt1：128895 / 155139  Accuracy 84.8633%
2. bulgarian: 57500 / 71493 Accuracy: 82.2346%
3. hanoi: 12839 / 17457 Accuracy: 73.5464%
4. magic: 40873 / 67869 Accuracy: 61.2680%
5. pi: 32374472 / 39956380 Accuracy: 81.9294%
6. qsort: 165102 / 200045 Accuracy: 88.0802%
7. queens: 53405 / 77116 Accuracy: 70.5535%
8. superloop: 376805 / 435027 Accuracy: 88.5890%
9. tak: 42972 / 60639 Accuracy: 73.9062%

### v5.4.1

搜索循环节2、3、4、5，参数为5、5、4、4

1. basicopt1：128895 / 155139  Accuracy 92.6988%
2. bulgarian: 57500 / 71493 Accuracy: 86.7386%
3. hanoi: 12839 / 17457 Accuracy: 73.5350%
4. magic: 40873 / 67869 Accuracy: 60.6369%
5. pi: 32374472 / 39956380 Accuracy: 82.0983%
6. qsort: 165102 / 200045 Accuracy: 87.4938%
7. queens: 53405 / 77116 Accuracy: 73.3855%
8. superloop: 376805 / 435027 Accuracy: 89.9825%
9. tak: 42972 / 60639 Accuracy: 74.086%

### v5.4.2 (TLE)

搜索循环节2、3、4、5、6，参数为6、5、4、4、3

1. basicopt1：128895 / 155139  Accuracy 92.6982%
2. bulgarian: 57500 / 71493 Accuracy: 85.2629%
3. hanoi: 12839 / 17457 Accuracy: 96.9181%
4. magic: 40873 / 67869 Accuracy: 60.6801%
5. pi: 32374472 / 39956380 Accuracy: 81.1564%
6. qsort: 165102 / 200045 Accuracy: 87.7573%
7. queens: 53405 / 77116 Accuracy: 75.0817%
8. superloop: 376805 / 435027 Accuracy: 90.5845%
9. tak: 42972 / 60639 Accuracy: 74.2311%

### v5.5

针对 v5.4.2 中 PI 的 TLE 进行了改进。

- 对于 50,000 次以内的预测，搜索长度为 2，3，4，5，6 的循环节

- 对于 500,000 次以内的预测，搜索长度为2，3，4，5的循环节
- 其余搜索长度为2，3的循环节。

(参数分别为 6，5，4，4，3)

1. basicopt1：128895 / 155139  Accuracy 92.6982%
2. bulgarian: 57500 / 71493 Accuracy: 85.2629%
3. hanoi: 12839 / 17457 Accuracy: 96.9181%
4. magic: 40873 / 67869 Accuracy: 60.6801%
5. pi: 32374472 / 39956380 Accuracy: 81.1499%
6. qsort: 165102 / 200045 Accuracy: 87.7573%
7. queens: 53405 / 77116 Accuracy: 75.0817%
8. superloop: 376805 / 435027 Accuracy: 90.5845%
9. tak: 42972 / 60639 Accuracy: 74.2311%