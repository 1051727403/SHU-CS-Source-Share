#pragma once
#ifndef CxxllMB
#define CxxllMB
#include<iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include<algorithm>
using namespace std;

// Cxxll----------------------------------------------------------
template<class T>
class Cxxll
{
public:
	Cxxll(const unsigned int Size=0, const T* Head=NULL);			//���캯��
	Cxxll(const Cxxll& v);								//�������캯��
	virtual ~Cxxll();										//��������������Ҫ�ͷ��ڴ棬���������ͷ�
	Cxxll& operator=(const Cxxll& v);						//��ֵ���㺯��
	unsigned int getsize() const;							//����������С
	void resize(unsigned int Size);							//��������
	void insert(const T val, const unsigned int& pos, const unsigned int &n); //��posλ�ú����n��Ԫ��val
	void erase(const unsigned int& pos);//ɾ��posλ�õ�һ��Ԫ��,�±�Խ���׳��쳣
	void erase(const unsigned int& lt, const unsigned int& rt);//�������أ�ɾ����[left,right]�������ڵ�����Ԫ�ء�
	bool empty() const;//�ж������Ƿ�Ϊ��
	void clear();//�������Ԫ��
	void swap(Cxxll<T>& v);//����������v����;
	void reverse();//��ת����
	T& operator[](const unsigned int& pos)const throw(int);//�����±�Ϊpos��Ԫ��

	virtual void putout(ostream& out) const = 0;			//���麯��
	virtual void putin(istream& in) = 0;
protected:
	unsigned int size;
	T* head;
};

// Cxxll�Ĵ���----------------------------------------------------
template <typename T>											// ���캯��
Cxxll<T>::Cxxll(const unsigned int Size, const T* Head) {
	//size = (Size > 0) ? size : 0;
	size = Size;
	head = NULL;
	if (size > 0) {
		head = new T[size+1];
		for (int i = 0; i < size; i++)
			head[i] = (Head == NULL) ? 0 : Head[i];
	}
}
template<class T>											// ��������
Cxxll<T>::~Cxxll() {
	delete []head;
	this->head = NULL;
	this->size = 0;
};

template <class T>											// ��ֵ���㺯��
Cxxll<T>& Cxxll<T>::operator=(const Cxxll<T>& v) {
	if (head == v.head) return *this;
	if (size != v.size) {
		if (head != NULL) delete head;
		head = new T[size = v.size];
	}
	for (int i = 0; i < size; i++) {
		head[i] = v.head[i];
	}
	return *this;
}

template <class T>											// �������캯��
Cxxll<T>::Cxxll(const Cxxll<T>& v) {
	size = 0;
	head = NULL;
	*this = v;
}
// Cxxll----------------------------------------------------------

template <typename T>
void Cxxll<T>::resize(unsigned int Size)			// ָ��������ά������������ԭ�е����ݣ�
{
	if (Size < 0 || Size == size)
		return;
	else if (Size == 0)
	{
		if (head != NULL) delete[] head;
		head = NULL;
		size = 0;
	}
	else
	{
		T* temp = head;
		head = new T[Size];
		for (int i = 0; i < Size; i++)
			head[i] = (i < size) ? temp[i] : 0;	// ��������ԭ������
		size = Size;
		delete[] temp;
	}
}
template<typename T>
void Cxxll<T>::insert(const T val, const unsigned int &pos, const unsigned int &n) {
	int temp = size;
	resize(size+n);
	for (int i = temp-1; i >= pos; --i) head[i + n] = head[i];
	for (int i = pos; i < pos + n; i++) head[i] = val;
}
template<typename T>
void Cxxll<T>::erase(const unsigned int& pos) {
	try {
		if (pos < 0 || pos >= size) throw - 1;
		erase(pos, pos);
	}
	catch (int e) {
		cerr << "error:�±�Խ��" << endl;
	}
}
template<typename T>
void Cxxll<T>::erase(const unsigned int& lt, const unsigned int &rt) {
	try {
		if (rt >= size || lt >= size || lt < 0 || rt < 0 || lt > rt) throw - 1;
		else {
			int lenth = rt - lt + 1;
			size -= lenth;
			for (int i = lt; i < size; i++) head[i] = head[i + lenth];
		}
	}
	catch (int e) {
		cerr << "error:�±�Խ��" << endl;
	}
}
template<typename T>
bool Cxxll<T>::empty() const{
	return (size == 0);
}
template <typename T>
T& Cxxll<T>::operator[](const unsigned int& index) const throw(int)// ��������������������÷��أ�������ֵ��
{
	try{
		if (head == NULL)
			throw 0;							// ����ӵ��쳣
		if (index < 0 || index >= size)
			throw - 1;
		return head[index];
	}
	catch (int e)
	{
		cout << "�±�Խ�磡" << endl;
	}
}

template <class T>
unsigned int Cxxll<T>::getsize() const {
	return size;
}

template <class T>											// 16 Pineklll �����������Ԫ��
void Cxxll<T>::clear() {
	size = 0;
	delete[]head;
	head = NULL;
}

template <class T>											// 18 Pineklll ����������v����
void Cxxll<T>::swap(Cxxll<T>& v) {
	T* temp;
	unsigned int t_size;
	t_size = size;
	size = v.size;
	v.size = t_size;
	temp = head;
	head = v.head;
	v.head = temp;

}
template<typename T>
void Cxxll<T>::reverse(){
	T* tmp = new T;
	memset(tmp, 0, sizeof(T));
	for (int i = 0; i < size / 2; i++) {
		*tmp = head[i];
		head[i] = head[size - 1 - i];
		head[size - 1 - i] = *tmp;
	}
}
// Cxxll�������--------------------------------------------------
template <class T>											//�������
ostream& operator<<(ostream& out, const Cxxll<T>& v) {
	v.putout(out);
	return out;
}

template <class T>											//��������
istream& operator>>(istream& in, Cxxll<T>& v) {
	v.input(in);
	return in;
}

// Cxxll���Ժ���--------------------------------------------------


#endif