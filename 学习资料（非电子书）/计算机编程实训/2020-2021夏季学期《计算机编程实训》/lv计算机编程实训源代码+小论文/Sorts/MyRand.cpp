// MyRand.cpp		产生服从高斯分布（正态分布）和均匀分布的随机数
#include <cstdlib>
#include <ctime>
#include <cmath>

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
double GaussRand(double mean, double variance)	// mena:均值、数学期望，variance方差
{
	static double u, v;
	static int phase = 0;
	double z;

	if(phase == 0)
	{
		u = (rand() + 1.0) / (RAND_MAX + 1.0);	// 避免u或v为0时参与对数log计算
		v = (rand() + 1.0) / (RAND_MAX + 1.0);
		z = sqrt(-2.0 * log(u))* sin(2.0 * M_PI * v);
	}
	else
	{
		z = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
	}
	phase = 1 - phase;
	return mean + z*sqrt(variance);
}

// 利用rand()产生0~RAND_MAX之间的"均匀"分布的随机整数，进行简单的线性变换
double UniformRand(double a, double b)			// 区间[a, b]上的均匀分布
{
	return a + rand()*(b-a)/RAND_MAX;			// 经过两点(0,a)和(RAND_MAX,b)的直线方程
}
