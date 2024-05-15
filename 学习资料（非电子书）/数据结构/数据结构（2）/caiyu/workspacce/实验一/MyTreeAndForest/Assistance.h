#ifndef __ASSISTANCE_H__				// ���û�ж���__ASSISTANCE_H__
#define __ASSISTANCE_H__				// ��ô����__ASSISTANCE_H__

// ���������

// ANSI C++��׼��ͷ�ļ�
#include <cstring>					// ��׼������
#include <iostream>					// ��׼������
#include <limits>					// ����
#include <cmath>					// ���ݺ���
#include <fstream>					// �ļ��������
#include <cctype>					// �ַ�����
#include <ctime>       				// ���ں�ʱ�亯��
#include <cstdlib>					// ��׼��
#include <cstdio>       			// ��׼�������
#include <iomanip>					// �����������ʽ����	
#include <cstdarg> 					// ֧�ֱ䳤��������	
#include <cassert>					// ֧�ֶ���
using namespace std;				// ��׼������������ռ�std��

// �Զ�������
enum Status {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};

// �궨��
#define DEFAULT_SIZE 1000			// ȱʡԪ�ظ���
#define DEFAULT_INFINITY 1000000	// ȱʡ�����


// ������������

char GetChar(istream &inStream = cin); // ��������inStream�������ո��Ʊ����ȡһ�ַ�

template <class ElemType >
void Swap(ElemType &e1, ElemType &e2);	// ����e1, e2ֵ֮

template<class ElemType>
void Display(ElemType elem[], int n);	// ��ʾ����elem�ĸ�����Ԫ��ֵ

template <class ElemType>
void Write(const ElemType &e);			// ��ʾ����Ԫ��

// ������
class Error;			// ͨ���쳣��

char GetChar(istream &inStream)
// �����������������inStream�������ո��Ʊ����ȡһ�ַ�
{
	char ch;								// ��ʱ����
	while ((ch = (inStream).peek()) != EOF	// �ļ�������(peek()�������������н���1
											// �ַ�,���ĵ�ǰλ�ò���)
		&& ((ch = (inStream).get()) == ' '	// �ո�(get()�������������н���1�ַ�,��
											// �ĵ�ǰλ�������1��λ��)
		|| ch == '\t'));					// �Ʊ��
	
	return ch;								// �����ַ�
}


// ͨ���쳣��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
#define MAX_ERROR_MESSAGE_LEN 100
class Error
{
private:
// ���ݳ�Ա
	char message[MAX_ERROR_MESSAGE_LEN];// �쳣��Ϣ

public:
//  ��������
	Error(const char *mes = "һ�����쳣!");	// ���캯�� 
	~Error(void) {};					// ��������	
	void Show() const;					// ��ʾ�쳣��Ϣ
};

// ͨ���쳣���ʵ�ֲ���
Error::Error(const char *mes)
// �����������mes����ͨ���쳣����
{
	strcpy(message, mes);				// �����쳣��Ϣ
}

void Error::Show()const
// �����������ʾ�쳣��Ϣ
{
	cout << message << endl;			// ��ʾ�쳣��Ϣ	
}


template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
// �������: ����e1, e2ֵ֮
{
	ElemType temp;		// ��ʱ����
	// ѭ����ֵʵ�ֽ���e1, e2
	temp = e1;	e1 = e2;  e2 = temp;
}

template<class ElemType>
void Display(ElemType elem[], int n)
// �������: ��ʾ����elem�ĸ�����Ԫ��ֵ
{
	for (int i = 0; i < n; i++)
	{	// ��ʾ����elem
		cout << elem[i] << "  ";
	}
	cout << endl; 
}

template <class ElemType>
void Write(const ElemType &e)
// �������: ��ʾ����Ԫ��
{
    cout << e << "  ";
}

#endif
