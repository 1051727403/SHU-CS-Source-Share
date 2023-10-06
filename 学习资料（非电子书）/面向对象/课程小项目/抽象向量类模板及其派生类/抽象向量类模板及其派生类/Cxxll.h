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
	Cxxll(const unsigned int Size=0, const T* Head=NULL);			//构造函数
	Cxxll(const Cxxll& v);								//拷贝构造函数
	virtual ~Cxxll();										//析构函数，不需要释放内存，在子类中释放
	Cxxll& operator=(const Cxxll& v);						//赋值运算函数
	unsigned int getsize() const;							//返回向量大小
	void resize(unsigned int Size);							//调整容量
	void insert(const T val, const unsigned int& pos, const unsigned int &n); //在pos位置后插入n个元素val
	void erase(const unsigned int& pos);//删除pos位置的一个元素,下标越界抛出异常
	void erase(const unsigned int& lt, const unsigned int& rt);//函数重载，删除从[left,right]闭区间内的所有元素。
	bool empty() const;//判断向量是否为空
	void clear();//清除向量元素
	void swap(Cxxll<T>& v);//将本向量和v交换;
	void reverse();//翻转向量
	T& operator[](const unsigned int& pos)const throw(int);//返回下标为pos的元素

	virtual void putout(ostream& out) const = 0;			//纯虚函数
	virtual void putin(istream& in) = 0;
protected:
	unsigned int size;
	T* head;
};

// Cxxll四大函数----------------------------------------------------
template <typename T>											// 构造函数
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
template<class T>											// 析构函数
Cxxll<T>::~Cxxll() {
	delete []head;
	this->head = NULL;
	this->size = 0;
};

template <class T>											// 赋值运算函数
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

template <class T>											// 拷贝构造函数
Cxxll<T>::Cxxll(const Cxxll<T>& v) {
	size = 0;
	head = NULL;
	*this = v;
}
// Cxxll----------------------------------------------------------

template <typename T>
void Cxxll<T>::resize(unsigned int Size)			// 指定向量的维数（尽量保留原有的数据）
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
			head[i] = (i < size) ? temp[i] : 0;	// 尽量保留原有数据
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
		cerr << "error:下标越界" << endl;
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
		cerr << "error:下标越界" << endl;
	}
}
template<typename T>
bool Cxxll<T>::empty() const{
	return (size == 0);
}
template <typename T>
T& Cxxll<T>::operator[](const unsigned int& index) const throw(int)// 方括号运算符函数（引用返回，可作左值）
{
	try{
		if (head == NULL)
			throw 0;							// 新添加的异常
		if (index < 0 || index >= size)
			throw - 1;
		return head[index];
	}
	catch (int e)
	{
		cout << "下标越界！" << endl;
	}
}

template <class T>
unsigned int Cxxll<T>::getsize() const {
	return size;
}

template <class T>											// 16 Pineklll 清除向量所有元素
void Cxxll<T>::clear() {
	size = 0;
	delete[]head;
	head = NULL;
}

template <class T>											// 18 Pineklll 将本向量与v交换
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
// Cxxll输入输出--------------------------------------------------
template <class T>											//输出重载
ostream& operator<<(ostream& out, const Cxxll<T>& v) {
	v.putout(out);
	return out;
}

template <class T>											//输入重载
istream& operator>>(istream& in, Cxxll<T>& v) {
	v.input(in);
	return in;
}

// Cxxll测试函数--------------------------------------------------


#endif