// Main.cpp
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#include "Sorts.h"
#include "Score.h"
#include "MyRand.h"
#include "SortString.h"
using namespace std;
typedef unsigned long long ULL;


double gettime(int restart)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	const double c = 1.0 / CLOCKS_PER_SEC;
	static clock_t t = clock();				// 静态局部变量。第一次调用时，确定计时起点
	if (restart) t = clock();				// 根据实参决定是否重新确定计时起点
	return c * (clock() - t);					// 从上一计时点到现在所经历的时间
}

template <typename T> void InitData(T* data, const int& n, const int& flag)
{
	int i;
	switch (flag)
	{
	case -1: for (i = 0; i < n; i++) data[i] = n - 1 - i;break;					// 逆序（从大到小）
	case 0:	 for (i = 0; i < n; i++) data[i] = i;break;							// 顺序（从小到大）
	case 1:  for (i = 0; i < n; i++) data[i] = (T)UniformRand(54, 90); break;	// [54,90]上的均匀分布
	default: for (i = 0; i < n; i++) data[i] = (T)GaussRand(72, 6 * 6); break;	// 正态分布，均值72，方差36（根方差6）
	}
}

// 调用本函数的实参的值不重要，重要的是实参的数据类型
template <typename T> void Test(const T& x, int first, int second, bool out)
{
	char algo[][20] = { "归并","归并优化"/*,"内置"*/,"冒泡","冒泡优化","选排","选排优化","快排","快排优化" };
	void (*f[])(T*, int, ULL&, ULL&) = { mergeSort,mergeSortPlus/*,_sort*/,Bubble,g_Bubble,Select,Select_Primer,Qsort,g_Qsort };		// 函数指针数组（元素为一系列函数的入口地址）
	int m = (sizeof(f) / sizeof(*f));						// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	T* data0 = NULL, * data = NULL;													// 两个指针初始化为NULL非常重要！
	char InitConf[][20] = { "完全逆序", "完全顺序", "均匀分布", "正态分布" };		// C-字符串数组
	bool flag[20];											// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];											// 同上。记录不同算法的执行时间
	ULL compareCnt = 0, assignCnt = 0;						// compareCnt记录比较次数，assignCnt记录赋值次数
	ULL* compareCnt_memory = new ULL[m], * assignCnt_memory = new ULL[m];
	for (int j = 2; j >= -1; j--)							// 数据分布类型
	{
		cout << "\n数据类型:" << typeid(T).name() << " (" << InitConf[j + 1] << ")" << endl;
		for (int i = first; i <= second; i++)
			cout << '\t' << algo[i];
		cout << endl;
		for (int n = 1024; n <= 65536; n *= 2)
		{
			GetMemory(data, data0, n);						// 申请分配堆空间
			InitData(data0, n, j);							// 设置原始数据
			cout << n;
			for (int i = first; i <= second; i++)
			{
				if (i == 6 && n == 65536 && (j == 0 || j == -1))
				{
					t[i] = -1;
					flag[i] = 0;
					continue;
				}
				ReSet(data, data0, n);						// 恢复原始数据
				gettime(1);									// 设置计时起点
				f[i](data, n, compareCnt, assignCnt);		// 第 i 种排序算法
				t[i] = gettime();							// 返回从计时起点到目前所经历的时间（秒）
				flag[i] = Check(data, n);
				compareCnt_memory[i] = compareCnt;
				assignCnt_memory[i] = assignCnt;
				compareCnt = 0, assignCnt = 0;
			}
			for (int i = first; i <= second; i++)
				cout << '\t' << t[i];
			cout << '\t';
			for (int i = first; i <= second; i++)
			{
				cout << "   " << algo[i] << (flag[i] ? ":正确" : ":错误");
				if (out) cout << "  比较:" << compareCnt_memory[i] << "   赋值:" << assignCnt_memory[i];
			}
			cout << endl;
			FreeMemory(data, data0);						// 释放堆空间资源，并使指针为空
		}
	}
	delete compareCnt_memory;
	delete assignCnt_memory;
}

void query(int& first, int& second, bool& out, const int& m)  // 询问函数
{
	cout << "\n\t| ---- 请选择排序方法-----|\n";
	cout << "\t| ---- 全部............(0)|\n";
	cout << "\t| ---- 归并排序........(1)|\n";
	cout << "\t| ---- 冒泡排序........(2)|\n";
	cout << "\t| ---- 选择排序........(3)|\n";
	cout << "\t| ---- 快速排序........(4)|\n";
	cout << "\t| ---- 字符排序........(5)|\n";
	cout << "\t| ---- 退出............(6)|\n";
	cout << "\t请输入: ";
	char mode;
	cin >> mode;
	if (mode < '0' || mode > '6') mode = '0';			// 其他表示排序全部
	if (mode == '6') first = -2;						// -2表示退出
	else if (mode == '5') first = -1;					// -1表示字符排序
	else if (mode == '0') { first = 0; second = m - 1; }
	else
	{
		first = (mode - '0' - 1) * 2;
		second = first + 1;
		cout << "\n\t是否输出比较次数和赋值次数(是:1 否:0):";
		char t;
		cin >> t;
		out = t - '0';
	}
}

int main()						// 主函数
{
	srand(time(NULL));			// 设置随机数发生器的种子
	char algo[][20] = { "归并","归并优化"/*,"内置"*/,"冒泡","冒泡优化","选排","选排优化","快排","快排优化" };
	int m = (sizeof(algo) / sizeof(*algo));						// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	while (true)
	{
		int first, second;
		bool out = false;
		query(first, second, out, m);
		if (first == -2) return 0;
		if (first == -1) { TestString(); continue; }
		/*first = 0;second = 2;*/
		Test(int(0), first, second, out);				// 测试int类型数据
		Test(double(0), first, second, out);
		TestScore(first, second);
	}
	return 0;
}
