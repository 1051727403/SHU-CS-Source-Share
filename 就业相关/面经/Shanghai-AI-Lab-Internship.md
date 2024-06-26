# Shanghai AI Lab (Internship) 面经

## 1. 大芯片中心-AI编译实习生-高性能计算方向 (成功)

> 这个成功案例由 jamesnulliu 提供, 有其他问题可以邮件咨询: jamesnulliu@gmail.com

### 1.1. 需求

主要干 Architecture, AI 的软硬件结合.

需要具备下述知识: 计算机系统结构, C/C++, Linux, 并行计算 (MPI, OpenMP), CUDA, 深度学习模型的部署, 推理, 训练和设计, 量化, 减枝.

> 本人上述内容都略有涉及, ASC24 获得 FIRST PRIZE, 在多个 AI 组搓模型作项目, SCI 一区通讯作者一篇. 这里宣传一下 SHUSCT (上海大学超算队).
>
> 另外, 如果你想投 AI Lab 的 CV 和 NLP 组, 最好要有若干篇 CCFA 发表才行; 其次这些组的面试要求似乎非常高, 比如手写 Multi-Head Attention.

### 1.2. 投递方式

我是 Boss 直接乱投, 大概投出去两天问我能实习多久, 再过了几天就有电话面试.

AI Lab 官网应该也能投; 我不是特别了解.

### 1.3. 一面

主要问项目经历, 因为有 ASC24 的奖项和高性能服务器维护经历, 所以面试官觉得挺合适的. 

问我有没有 AI 编译器的使用经验, 我说我都不知道这是啥, 他说正常一般本科生都不会用到这些东西.

考了一题连通图: 给一个 N*N 的矩阵, 其中 0 代表海洋 1 代表陆地, 求其中能构成几个岛屿.

### 1.4. 二面

一周后接到电话二面, 面试官好像是清华的博士, 比一面严厉多了, 我个人觉得自己答的不太好, 主要以下地方:

1. 解释 Flash Attention 原理: Flash Attention 中 KV 会有 softmax 操作; 我说 Q 也有, 被他指出了错误.
2. CUDA 经验: 问我怎么定义单线程上的操作，我卡壳了； 其实就是问 kernel 函数怎么写.
3. 问我怎么只有四级分数, 我说六级我有事没去考; 然后他说这四级分数还看起来挺高 (625), 我说我考多少写多少不是编的.

其他还是问经历和基础问题, 比如介绍一下你怎么优化并行软件之类的.

五天没收到回复, 发邮件问了一下面试官, 和我说过了后续会有 HR 对接.
