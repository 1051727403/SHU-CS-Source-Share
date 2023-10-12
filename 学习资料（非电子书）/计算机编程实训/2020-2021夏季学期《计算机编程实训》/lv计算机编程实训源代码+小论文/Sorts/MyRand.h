// MyRand.h		产生服从高斯分布（正态分布）和均匀分布的随机数
#ifndef MY_RAND_H
#define MY_RAND_H
/*
Box-Muller是产生随机数的一种方法。Box-Muller 算法隐含的原理非常深奥，但结果却是相当简单。
如果在(0,1]值域内有两个一致的随机数字u1和u2，则
可以使用以下两个式子中的任一个算出一个正态分布的随机数字z
z = r * cos(θ) 或 z = r * sin(θ)
其中 r = sqrt(-2 * ln(u2)), θ= 2 * π * u1
则z服从N(0, 1)，最后通过线性变换
x = m + (z * σ)服从N(m, σ^2)。
参见https://baike.baidu.com/item/box-muller/4023794?fr=aladdin
*/

double GaussRand(double mean=0, double variance=1);	// 正态分布(高斯分布) mena:均值、数学期望，variance方差
double UniformRand(double a=0, double b=1);			// 区间[a, b]上的均匀分布

#endif
