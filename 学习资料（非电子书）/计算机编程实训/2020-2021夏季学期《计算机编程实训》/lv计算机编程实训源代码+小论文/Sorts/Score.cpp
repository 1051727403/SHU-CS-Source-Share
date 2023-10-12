// Score.cpp
#include "MyRand.h"
#include "Score.h"
#include "Sorts.h"
#include <iostream>
#include <cstdio>
#include <typeinfo>
using namespace std;
typedef unsigned long long ULL;

void InitScore(Score* data, int n)
{
	double mean = 72, variance = 6 * 6;
	for (int i = 0; i < n; i++)
	{
		sprintf(data[i].Id, "%08d", i + 1);	// 请自学 sprintf 函数。请注意：原始数据中，学号是完全顺序排列的！
		data[i].Total = data[i].Chinese = int(0.5 + GaussRand(mean, variance));	// 加0.5后取整即小数部分"四舍五入"
		data[i].Total += data[i].Math = int(0.5 + GaussRand(mean, variance));
		data[i].Total += data[i].English = int(0.5 + GaussRand(mean, variance));
		data[i].Total += data[i].Physics = int(0.5 + GaussRand(mean, variance));
		data[i].Total += data[i].Chemistry = int(0.5 + GaussRand(mean, variance));
	}
}

void ShowScore(const Score* data, int size, int last)
{
	int m;
	if (last <= 0 || last >= size)
		m = 0;								// 所有数据
	else
		m = size - last;						// 最后last项数据
	cout << "\t倒序输出部分数据（即总分前若干名的数据）" << endl;
	cout << "\t 学 号  总分 语 数 外 理 化" << endl;
	for (int i = size - 1; i >= m; i--)
	{
		cout << '\t' << data[i].Id << ' ' << data[i].Total << ' '
			<< data[i].Chinese << ' ' << data[i].Math << ' '
			<< data[i].English << ' ' << data[i].Physics << ' '
			<< data[i].Chemistry;
		if (data[i].Total == data[i - 1].Total && data[i].Id < data[i - 1].Id) cout << ' ' << "fasle";
		cout << endl;
	}
}
void TestScore(int first, int second)
{
	char algo[][20] = { "归并","归并优化"/*,"内置"*/,"冒泡","冒泡优化","选排","选排优化","快排","快排优化" };
	Score* data0 = NULL, * data = NULL;							// 两个指针初始化为NULL非常重要！
	void (*f[])(Score*, int, unsigned long long&, unsigned long long&) = { mergeSort,mergeSortPlus,Bubble,g_Bubble,Select,Select_Primer,Qsort,g_Qsort };
	int n;													// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	bool flag;
	double t;
	ULL compareCnt = 0, assignCnt = 0;
	while (second >= first)
	{
		if (first % 2 == 0) {
			cout << "优化前:" << "------------------------------------------------------------------" << endl;
		}
		else {
			cout << "\n优化后:" << "------------------------------------------------------------------" << endl;
		}
		cout << "\n原始数据分布: 正态分布, 数据类型 = " << typeid(Score).name() << endl;
		for (n = 1024; n <= 65536; n *= 2)
		{
			GetMemory(data, data0, n);						// 申请分配堆空间
			InitScore(data0, n);							// 设置原始数据
			ReSet(data, data0, n);							// 恢复原始数据
			gettime(1);										// 设置计时起点
			f[first](data, n, compareCnt, assignCnt);	    // 第 i 种排序算法
			t = gettime();									// 返回从计时起点到目前所经历的时间（秒）
			flag = Check(data, n);							// 检验排序的正确性
			cout << n << '\t' << t << '\t' << algo[first] << (flag ? ": 正确" : ": 错误") << endl;
			ShowScore(data, n, 10);
			cout << '\t' << "比较次数：" << compareCnt << '\t' << "赋值次数：" << assignCnt << endl;
			compareCnt = 0, assignCnt = 0;						// 倒序输出最后10项（由于按升序排列，最高分第一名在最后）
			FreeMemory(data, data0);						// 释放堆空间资源，并使指针为空
		}
		++first;
	}
}
