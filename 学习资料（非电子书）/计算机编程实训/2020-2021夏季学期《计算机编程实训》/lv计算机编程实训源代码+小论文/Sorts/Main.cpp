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


double gettime(int restart)					// ������Ĭ��ֵ�������ʾ���¼�ʱ
{											// �����ۼƼ�ʱ
	const double c = 1.0 / CLOCKS_PER_SEC;
	static clock_t t = clock();				// ��̬�ֲ���������һ�ε���ʱ��ȷ����ʱ���
	if (restart) t = clock();				// ����ʵ�ξ����Ƿ�����ȷ����ʱ���
	return c * (clock() - t);					// ����һ��ʱ�㵽������������ʱ��
}

template <typename T> void InitData(T* data, const int& n, const int& flag)
{
	int i;
	switch (flag)
	{
	case -1: for (i = 0; i < n; i++) data[i] = n - 1 - i;break;					// ���򣨴Ӵ�С��
	case 0:	 for (i = 0; i < n; i++) data[i] = i;break;							// ˳�򣨴�С����
	case 1:  for (i = 0; i < n; i++) data[i] = (T)UniformRand(54, 90); break;	// [54,90]�ϵľ��ȷֲ�
	default: for (i = 0; i < n; i++) data[i] = (T)GaussRand(72, 6 * 6); break;	// ��̬�ֲ�����ֵ72������36��������6��
	}
}

// ���ñ�������ʵ�ε�ֵ����Ҫ����Ҫ����ʵ�ε���������
template <typename T> void Test(const T& x, int first, int second, bool out)
{
	char algo[][20] = { "�鲢","�鲢�Ż�"/*,"����"*/,"ð��","ð���Ż�","ѡ��","ѡ���Ż�","����","�����Ż�" };
	void (*f[])(T*, int, ULL&, ULL&) = { mergeSort,mergeSortPlus/*,_sort*/,Bubble,g_Bubble,Select,Select_Primer,Qsort,g_Qsort };		// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int m = (sizeof(f) / sizeof(*f));						// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	T* data0 = NULL, * data = NULL;													// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char InitConf[][20] = { "��ȫ����", "��ȫ˳��", "���ȷֲ�", "��̬�ֲ�" };		// C-�ַ�������
	bool flag[20];											// ������Ϊ������20�㹻���ڱ��� m����¼��ͬ�㷨ִ�е���ȷ��
	double t[20];											// ͬ�ϡ���¼��ͬ�㷨��ִ��ʱ��
	ULL compareCnt = 0, assignCnt = 0;						// compareCnt��¼�Ƚϴ�����assignCnt��¼��ֵ����
	ULL* compareCnt_memory = new ULL[m], * assignCnt_memory = new ULL[m];
	for (int j = 2; j >= -1; j--)							// ���ݷֲ�����
	{
		cout << "\n��������:" << typeid(T).name() << " (" << InitConf[j + 1] << ")" << endl;
		for (int i = first; i <= second; i++)
			cout << '\t' << algo[i];
		cout << endl;
		for (int n = 1024; n <= 65536; n *= 2)
		{
			GetMemory(data, data0, n);						// �������ѿռ�
			InitData(data0, n, j);							// ����ԭʼ����
			cout << n;
			for (int i = first; i <= second; i++)
			{
				if (i == 6 && n == 65536 && (j == 0 || j == -1))
				{
					t[i] = -1;
					flag[i] = 0;
					continue;
				}
				ReSet(data, data0, n);						// �ָ�ԭʼ����
				gettime(1);									// ���ü�ʱ���
				f[i](data, n, compareCnt, assignCnt);		// �� i �������㷨
				t[i] = gettime();							// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
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
				cout << "   " << algo[i] << (flag[i] ? ":��ȷ" : ":����");
				if (out) cout << "  �Ƚ�:" << compareCnt_memory[i] << "   ��ֵ:" << assignCnt_memory[i];
			}
			cout << endl;
			FreeMemory(data, data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
	}
	delete compareCnt_memory;
	delete assignCnt_memory;
}

void query(int& first, int& second, bool& out, const int& m)  // ѯ�ʺ���
{
	cout << "\n\t| ---- ��ѡ�����򷽷�-----|\n";
	cout << "\t| ---- ȫ��............(0)|\n";
	cout << "\t| ---- �鲢����........(1)|\n";
	cout << "\t| ---- ð������........(2)|\n";
	cout << "\t| ---- ѡ������........(3)|\n";
	cout << "\t| ---- ��������........(4)|\n";
	cout << "\t| ---- �ַ�����........(5)|\n";
	cout << "\t| ---- �˳�............(6)|\n";
	cout << "\t������: ";
	char mode;
	cin >> mode;
	if (mode < '0' || mode > '6') mode = '0';			// ������ʾ����ȫ��
	if (mode == '6') first = -2;						// -2��ʾ�˳�
	else if (mode == '5') first = -1;					// -1��ʾ�ַ�����
	else if (mode == '0') { first = 0; second = m - 1; }
	else
	{
		first = (mode - '0' - 1) * 2;
		second = first + 1;
		cout << "\n\t�Ƿ�����Ƚϴ����͸�ֵ����(��:1 ��:0):";
		char t;
		cin >> t;
		out = t - '0';
	}
}

int main()						// ������
{
	srand(time(NULL));			// ���������������������
	char algo[][20] = { "�鲢","�鲢�Ż�"/*,"����"*/,"ð��","ð���Ż�","ѡ��","ѡ���Ż�","����","�����Ż�" };
	int m = (sizeof(algo) / sizeof(*algo));						// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	while (true)
	{
		int first, second;
		bool out = false;
		query(first, second, out, m);
		if (first == -2) return 0;
		if (first == -1) { TestString(); continue; }
		/*first = 0;second = 2;*/
		Test(int(0), first, second, out);				// ����int��������
		Test(double(0), first, second, out);
		TestScore(first, second);
	}
	return 0;
}
