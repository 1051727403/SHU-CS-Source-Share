#ifndef VECTOR_H
#define VECTOR_H
#define _CRT_SECURE_NO_WARNINGS			// for VS2019
#pragma warning( disable : 4290 )		// for VS2019
#pragma warning( disable : 4996 )		// for VS2019
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;


//向量类模板定义-----------------------------------------------------------------------------------------------------------
template<class T>
class VECTOR
{
	template<typename U> friend ostream& operator<<(ostream& out, const VECTOR<U>& v);
private:
	T* arr;				//向量本体
	int size;			//向量大小
	int capacity;		//向量容量
public:
	VECTOR();									//普通构造,含初始大小,默认大小为4096；
	VECTOR(const int s);						//普通构造,容量为s;
	VECTOR(const VECTOR<T>& v);					//拷贝构造
	~VECTOR();									//析构函数
	//运算符重载函数
	VECTOR<T>& operator=(const VECTOR<T>& v);	//重载赋值运算符
	T& operator[](const int pos);				//重载[]运算符，下标越界抛出异常!!!!!!!!!!!!!!!!
	//未完成的运算符重载函数，待完成
	VECTOR<T> operator+(const VECTOR<T>& v);	//重载+运算符，实现两个数组各个位置元素相加后合并为一个数组；
												//但不同大小数组之间不能相加，若大小不同，抛出异常！！！！！！！！！！！！！
	VECTOR<T>& operator+=(const VECTOR<T>& v);	//同上


	//基础函数结束，成员函数定义开始-------------------------------------------------------------------------------------------
	void resize();								//自动扩展
	//增加部分
	void push_back(const T val);				//尾部插入一个元素
	void push_front(const T val);				//头部插入一个元素
	void insert(const T val, int pos);			//在pos位置后插入一个元素（从0开始）例：012insert（3,1）->0312
	void insert(const T val, int pos, int n);	//重载，在pos位置后插入n个元素val
	//删除部分
	void pop_back();							//在容器末尾删除一个元素
	void pop_front();							//在容器头部删除一个元素
	void erase(const int pos);				//删除pos位置的一个元素,下标越界抛出异常!!!!!!!!!!!!!!!!!!!!!
	void erase(const int lt, const int rt);	//函数重载，删除从[left,right]闭区间内的所有元素，下标越界抛出异常!!!!!!!!!!!!
	//获取信息部分
	T& front();								//获取头部元素
	T& back();									//获取尾部元素
	int getsize() const;						//返回容器大小
	int space();								//返回容器容量
	bool isempty();							//返回容器是否为空
	//杂项
	void reverse();							//逆置容器

	void input();								//从文件内读取内容到容器
	void output();								//输出容器内数据到文件
	//输出到文件格式：
	// 若文件内原来就有数据，则清空（写入文件时的类型设置）
	//第一行int或string或double等T类型的数据名称
	//（暂时不考虑结构体的输入输出，在输入文件函数中提示“结构体不可输入文件”，并由用户选择是否继续输入文件）
	//第二行一个‘[’
	//第三行开始每行输入20个数据，用空格分割
	//结尾单行‘]’表示结束并换行。

	//从文件内部读取格式：
	//第一行先getline判断该数据类型，构造相应的向量容器
	//下一行读取‘[’
	//下一行开始正式读取，每行有20个数据
	//读取到某行为‘]’则读取结束
	//查看下一行是否为空，若是，则跳出，否则继续按照上述过程读取；
};
//基础函数定义-------------------------------------------------------------------------------------------------------------
template<typename T>
VECTOR<T>::VECTOR() :size(0), capacity(4096) {
	arr = new T[capacity];
}
template<typename T>
VECTOR<T>::VECTOR(const int s) : size(s), capacity(2 * s) {
	//初始容量为2倍大小；
	arr = new T[capacity];
}
template<typename T>
VECTOR<T>::VECTOR(const VECTOR<T>& v) : size(v.size), capacity(v.capacity) {
	arr = new T[capacity];
	for (int i = 0; i < size; i++)
		arr[i] = v.arr[i];
}
template<typename T>
VECTOR<T>::~VECTOR() {
	delete[]arr;
	size = 0, capacity = 0;
}
template<typename T>
VECTOR<T>& VECTOR<T>::operator=(const VECTOR<T>& v) {
	//delete[]arr;
	//arr = new T[v.capacity];
	size = v.size;
	capacity = v.capacity;
	for (int i = 0; i < v.size; i++)
		arr[i] = v.arr[i];
	return *this;
}
template<typename T>
VECTOR<T> VECTOR<T>:: operator+(const VECTOR<T>& v) {
	VECTOR<T>* sum = new VECTOR<T>(v.size);
	try {
		if (size != v.size)
			throw - 1;
	}
	catch (int e) {
		cout << "can not take summation for two vector with different length." << endl;
		return *sum;
	}
	for (int i = 0; i < v.size; i++)
		(*sum)[i] = arr[i] + v.arr[i];
	return *sum;
}
template<typename T>
VECTOR<T>& VECTOR<T>:: operator+=(const VECTOR<T>& v) {
	try {
		if (size != v.size)
			throw -1;
	}
	catch (int e) {
		cout << "can not take summation for two vector with different length." << endl;
		return *this;
	}
	for (int i = 0; i < v.size; i++)
		arr[i] = arr[i] + v.arr[i];
	return *this;
}
template<typename T>
T& VECTOR<T>::operator[](const int pos) {
	try {
		if (pos >= size || pos < 0)throw - 1;
		else return arr[pos];
	}
	catch (int e) {
		cout << "数组下标越界" << endl;
	}
}
//基础函数定义结束，成员函数定义开始---------------------------------------------------------------------------------------
template<typename T>
void VECTOR<T>::resize() {
	T* temp = new T[size];
	for (int i = 0; i < size; i++)temp[i] = arr[i];
	capacity *= 2;
	delete[]arr;
	arr = new T[capacity];
	for (int i = 0; i < size; i++)arr[i] = temp[i];
	delete[] temp;
}
template<typename T>
void VECTOR<T>::push_back(const T val) {
	if (size == capacity)this->resize();
	arr[size++] = val;
}
template<typename T>
void VECTOR<T>::push_front(const T val) {
	if (size == capacity)this->resize();
	for (int i = size - 1; i >= 0; i--)arr[i + 1] = arr[i];
	arr[0] = val;
	size++;
}
template<typename T>
void VECTOR<T>::insert(const T val, int pos) {
	pos = max(pos, 0);
	pos = min(pos, size - 1);
	if (size == capacity)this->resize();
	for (int i = pos; i < size; i++)arr[i + 1] = arr[i];
	arr[pos] = val;
	size++;
}
template<typename T>
void VECTOR<T>::insert(const T val, int pos, int n) {
	pos = max(pos, 0);
	pos = min(pos, size - 1);
	if (n < 0) n = -n;
	while (size + n >= capacity) resize();
	for (int i = size-1; i >= pos; --i) arr[i + n] = arr[i];
	for (int i = pos; i < pos + n; i++) arr[i] = val;
	size += n;
}
template<typename T>
void VECTOR<T>::pop_back() {
	VECTOR<T> temp;
	try {
		temp.size = (this->size) - 1;
		if (temp.size < 0) throw - 1;
	}
	catch (int e) {
		cout << "下标越界" << endl;
		return;
	}
	for (int i = 0; i < temp.size; i++)
	{
		temp.arr[i] = this->arr[i];
	}
	delete[]arr;
	arr = new T[capacity];
	this->size = temp.size;
	for (int i = 0; i < temp.size; i++)
	{
		arr[i] = temp[i];
	}
}
template<typename T>
void VECTOR<T>::pop_front() {
	VECTOR<T> temp;
	try {
		temp.size = (this->size) - 1;
		if (temp.size < 0) throw - 1;
	}
	catch (int e) {
		cout << "下标越界" << endl;
		return;
	}
	for (int i = 0; i < temp.size; i++)temp.arr[i] = this->arr[i + 1];
		
	delete[]arr;
	arr = new T[capacity];
	this->size = temp.size;
	for (int i = 0; i < temp.size; i++) arr[i] = temp[i];
}
template<typename T>
void VECTOR<T>::erase(const int pos) {
	try {
		if (pos < 0 || pos >= size) throw - 1;
		erase(pos, pos);
	}
	catch (int e) {
		cerr << "error:下标越界" << endl;
	}
}
template<typename T>
void VECTOR<T>::erase(const int lt, const int rt) {
	try {
		if (rt >= size || lt >= size || lt < 0 || rt < 0 || lt > rt) throw - 1;
		else {
			int lenth = rt - lt + 1;
			size -= lenth;
			for (int i = lt; i < size; i++) arr[i] = arr[i + lenth];
		}
	}
	catch (int e) {
		cerr << "error:下标越界" << endl;
	}
}
template<typename T>
T& VECTOR<T>::front() {
	try {
		if (!size) throw - 1;
		else return arr[0];
	}
	catch (int e) {
		cerr << "\nerror:Segmentation fault\n";
	}
}
template<typename T>
T& VECTOR<T>::back() {
	try {
		if (!size) throw - 1;
		else return arr[size - 1];
	}
	catch (int e) {
		cerr << "\nerror:Segmentation fault\n";
	}
}
template<typename T>
int VECTOR<T>::getsize() const {
	return size;
}
template<typename T>
int VECTOR<T>::space() {
	return capacity;
}
template<typename T>
bool VECTOR<T>::isempty() {
	return (size == 0);
}
template<typename T>
void VECTOR<T>::reverse() {
	T* tmp = new T;
	memset(tmp, 0, sizeof(T));
	for (int i = 0; i < size / 2; i++){
		*tmp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = *tmp;
	}
}
template<typename U>
ostream& operator<<(ostream& out, const VECTOR<U>& v) {
	out << "VECTOR: （";
	for (int i = 0; i < v.size; i++)
	{
		out << v.arr[i] << " ";
	}
	out << ")";
	return out;
}
template<typename T>
void VECTOR<T>::input() {
	//std::cout << typeid(T).name() << endl;
	ifstream in;
	in.open("out.txt");
	if (in) {
		string s;
		int flag = 0;
		int flag1 = 0;
		while (getline(in, s)) {
			if (s == typeid(T).name()) {
				T x;
				getline(in, s);
				while (true) {
					for (int i = 0; i < 20; i++) {
						if (in >> x)
							push_back(x);
						else {
							flag = 1;
							break;
						}
					}
					if (flag) {
						flag1 = 1;
						break;
					}
				}
			}
			if (flag1 == 1) break;
		}
		if (flag1 == 0) cerr << "\nerror:cannot find the vector.\n";
		in.close();
	}
	else {
		cerr << "\nerror:reading file failed.\n";
	}
}
template<typename T>
void VECTOR<T>::output() {
	ofstream out("out.txt", ofstream::trunc);
	if (out)
	{
		out << typeid(T).name() << "\n[\n";
		int i = 0;
		for (; i < size / 20; i++)
		{
			for (int j = 0; j < 20; j++)
				out << arr[i * 20 + j] << ' ';
			out << endl;
		}
		for (int j = 0; j < size % 20; j++)
			out << arr[j + i * 20] << ' ';
		if (size % 20) out << endl;
		out << "]\n";
		out.close();
	}
	else {
		cerr << "\nerror:opening file failed.\n";
	}
}


#endif