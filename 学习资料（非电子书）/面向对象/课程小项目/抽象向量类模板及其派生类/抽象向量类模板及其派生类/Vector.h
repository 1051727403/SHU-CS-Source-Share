// Vector.h
#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include "Cxxll.h"
using namespace std;

// Vector---------------------------------------------------------
template<class T>
class  Vector :public Cxxll<T>
{
public:					
	Vector(const unsigned int size = 0, const T* x = NULL);
	Vector(const Vector<T>& v);							// ������ģ���������캯��
	void assign(const Vector<T>& v);					// ��ֵ����
	void push_back(const T val);
	void pop_back();//����β��Ԫ��
	T back();//����β��Ԫ��
	Vector<T> operator+(const Vector<T>& v);//�������ԭ�򣬲�ͬά���ܼ�
	Vector<T>& operator+=(const Vector<T>& v);//ͬ��,ע���Լ�
	void putout(ostream& out)const;//�ԣ�X1��X2��...,Xn������ʽ���
	void putin(istream& in);//�ԣ�X1��X2��...,Xn������ʽ����
};

// Vector---------------------------------------------------------
// �����๹�캯�����д��
template<class T>
Vector<T>::Vector(const unsigned int size, const T* x) : Cxxll<T>(size, x) {}		// ���캯��


template<class T>
Vector<T>::Vector(const Vector<T>& v) :Cxxll<T>(v) {
}

// 28 Pineklll putout()
template<class T>
void Vector<T>::putout(ostream& out) const {
	out << "(";
	if (this->size == 0) {
		out << ")";
		return;
	}
	for (int i = 0; i < this->size - 1; i++) {
		out << this->head[i] << ",";
	}
	out << this->head[this->size - 1] << ")";
	return;
};
// 27 Pineklll putin()
template<class T>
void Vector<T>::putin(istream& in) {
	const int M = 1024, N = 1;//1024;	// Nȡ��Сֵ1��Ϊ�˵��ԣ�ʵ��ʹ��ʱȡ1024
	Vector<T> temp;
	char str[M], ch;				// ch��ʼ��Ϊһ����')'�ַ�����
	T buffer[N];
	int i, j, k;

	in.getline(str, M, '(');		// ���˵�'('��֮ǰ�������ַ�
	while (true)						// ���˵���Բ����֮��Ŀհ��ַ�
	{
		ch = in.peek();				// ͵����һ���ַ������Ƿ�Ϊ�հ��ַ�
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			in.get(ch);				// ���ǿհ��ַ�������˵�������ȡ���ã�
		else
			break;					// ֱ�������ǿհ��ַ���������whileѭ��
	}

	if (in.peek() == ')')				// ͵����һ���ַ�������')'
	{
		this->resize(0);			// ���������ά�����ó� 0 ά
		in.get(ch);					// ��ȡ')'��ֹ����Ƕ��ʱ����
		return;						// �˳�������������Ϊ 0 ά����
	}

	for (k = 0; ch != ')'; k++)
	{
		for (i = 0; i < N && ch != ')'; i++)
			in >> buffer[i] >> ch;
		temp.resize(k * N + i);			// ������resize������"����������ԭ������"�Ĺ���
		for (j = 0; j < i; j++)
			temp[k * N + j] = buffer[j];// �����˷����������
	}
	*this = temp;					// �����˸�ֵ��������ֵ���㣩
};

// 17 Pineklll �ֵ
template<class T>
void Vector<T>::assign(const Vector<T>& v) {
	*this = v;	
}
template<typename T>
void Vector<T>::push_back(const T val) {
	this->resize(this->size+1);
	this->head[this->size-1] = val;
}
template<class T>
void Vector<T>::pop_back() {
	Vector<T> temp(*this);
	try {
		if (temp.size ==0) throw - 1;
		
	}
	catch (int e) {
		cout << "�±�Խ��" << endl;
		return;
	}
	delete[]this->head;
		this->head = new T[temp.size-1];
		this->size = temp.size-1;
		for (int i = 0; i < temp.size-1; i++)
		{
			this->head[i] = temp[i];
		}
}
template<class T>
T Vector<T>::back(){
	try {
		if (this->size==0) throw - 1;
		else return this->head[this->size - 1];
	}
	catch (int e) {
		cerr << "\nerror:Segmentation fault\n";
	}
}
template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& v) {
	Vector<T> temp(*this);
	try {
		if (this->size != v.size) throw-1;			//�쳣�׳�
		else {
			
			for (int i = 0; i < this->size; i++) {
				temp.head[i] +=v.head[i];
			}
			return temp;
		}
	}
	catch (int e)
	{
		cout << "��ͬά���������" << endl;
		return temp;
	}
}

// 27 Pineklll operator+=
template<class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& v) {
	try {
		if (this->size != v.size) throw(-1);			//�쳣�׳�
		else {
			for (int i = 0; i < this->size; i++) {
				this->head[i] = this->head[i] + v.head[i];
			}
			return *this;
		}
	}
	catch (int e)
	{
		cout << "��ͬά���������" << endl;
		return *this;
	}
}


// Vector---------------------------------------------------------
#endif