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
		sprintf(data[i].Id, "%08d", i + 1);	// ����ѧ sprintf ��������ע�⣺ԭʼ�����У�ѧ������ȫ˳�����еģ�
		data[i].Total = data[i].Chinese = int(0.5 + GaussRand(mean, variance));	// ��0.5��ȡ����С������"��������"
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
		m = 0;								// ��������
	else
		m = size - last;						// ���last������
	cout << "\t��������������ݣ����ܷ�ǰ�����������ݣ�" << endl;
	cout << "\t ѧ ��  �ܷ� �� �� �� �� ��" << endl;
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
	char algo[][20] = { "�鲢","�鲢�Ż�"/*,"����"*/,"ð��","ð���Ż�","ѡ��","ѡ���Ż�","����","�����Ż�" };
	Score* data0 = NULL, * data = NULL;							// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	void (*f[])(Score*, int, unsigned long long&, unsigned long long&) = { mergeSort,mergeSortPlus,Bubble,g_Bubble,Select,Select_Primer,Qsort,g_Qsort };
	int n;													// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	bool flag;
	double t;
	ULL compareCnt = 0, assignCnt = 0;
	while (second >= first)
	{
		if (first % 2 == 0) {
			cout << "�Ż�ǰ:" << "------------------------------------------------------------------" << endl;
		}
		else {
			cout << "\n�Ż���:" << "------------------------------------------------------------------" << endl;
		}
		cout << "\nԭʼ���ݷֲ�: ��̬�ֲ�, �������� = " << typeid(Score).name() << endl;
		for (n = 1024; n <= 65536; n *= 2)
		{
			GetMemory(data, data0, n);						// �������ѿռ�
			InitScore(data0, n);							// ����ԭʼ����
			ReSet(data, data0, n);							// �ָ�ԭʼ����
			gettime(1);										// ���ü�ʱ���
			f[first](data, n, compareCnt, assignCnt);	    // �� i �������㷨
			t = gettime();									// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
			flag = Check(data, n);							// �����������ȷ��
			cout << n << '\t' << t << '\t' << algo[first] << (flag ? ": ��ȷ" : ": ����") << endl;
			ShowScore(data, n, 10);
			cout << '\t' << "�Ƚϴ�����" << compareCnt << '\t' << "��ֵ������" << assignCnt << endl;
			compareCnt = 0, assignCnt = 0;						// ����������10����ڰ��������У���߷ֵ�һ�������
			FreeMemory(data, data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
		++first;
	}
}
