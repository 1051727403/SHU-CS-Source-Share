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


//������ģ�嶨��-----------------------------------------------------------------------------------------------------------
template<class T>
class VECTOR
{
	template<typename U> friend ostream& operator<<(ostream& out, const VECTOR<U>& v);
private:
	T* arr;				//��������
	int size;			//������С
	int capacity;		//��������
public:
	VECTOR();									//��ͨ����,����ʼ��С,Ĭ�ϴ�СΪ4096��
	VECTOR(const int s);						//��ͨ����,����Ϊs;
	VECTOR(const VECTOR<T>& v);					//��������
	~VECTOR();									//��������
	//��������غ���
	VECTOR<T>& operator=(const VECTOR<T>& v);	//���ظ�ֵ�����
	T& operator[](const int pos);				//����[]��������±�Խ���׳��쳣!!!!!!!!!!!!!!!!
	//δ��ɵ���������غ����������
	VECTOR<T> operator+(const VECTOR<T>& v);	//����+�������ʵ�������������λ��Ԫ����Ӻ�ϲ�Ϊһ�����飻
												//����ͬ��С����֮�䲻����ӣ�����С��ͬ���׳��쳣��������������������������
	VECTOR<T>& operator+=(const VECTOR<T>& v);	//ͬ��


	//����������������Ա�������忪ʼ-------------------------------------------------------------------------------------------
	void resize();								//�Զ���չ
	//���Ӳ���
	void push_back(const T val);				//β������һ��Ԫ��
	void push_front(const T val);				//ͷ������һ��Ԫ��
	void insert(const T val, int pos);			//��posλ�ú����һ��Ԫ�أ���0��ʼ������012insert��3,1��->0312
	void insert(const T val, int pos, int n);	//���أ���posλ�ú����n��Ԫ��val
	//ɾ������
	void pop_back();							//������ĩβɾ��һ��Ԫ��
	void pop_front();							//������ͷ��ɾ��һ��Ԫ��
	void erase(const int pos);				//ɾ��posλ�õ�һ��Ԫ��,�±�Խ���׳��쳣!!!!!!!!!!!!!!!!!!!!!
	void erase(const int lt, const int rt);	//�������أ�ɾ����[left,right]�������ڵ�����Ԫ�أ��±�Խ���׳��쳣!!!!!!!!!!!!
	//��ȡ��Ϣ����
	T& front();								//��ȡͷ��Ԫ��
	T& back();									//��ȡβ��Ԫ��
	int getsize() const;						//����������С
	int space();								//������������
	bool isempty();							//���������Ƿ�Ϊ��
	//����
	void reverse();							//��������

	void input();								//���ļ��ڶ�ȡ���ݵ�����
	void output();								//������������ݵ��ļ�
	//������ļ���ʽ��
	// ���ļ���ԭ���������ݣ�����գ�д���ļ�ʱ���������ã�
	//��һ��int��string��double��T���͵���������
	//����ʱ�����ǽṹ�������������������ļ���������ʾ���ṹ�岻�������ļ����������û�ѡ���Ƿ���������ļ���
	//�ڶ���һ����[��
	//�����п�ʼÿ������20�����ݣ��ÿո�ָ�
	//��β���С�]����ʾ���������С�

	//���ļ��ڲ���ȡ��ʽ��
	//��һ����getline�жϸ��������ͣ�������Ӧ����������
	//��һ�ж�ȡ��[��
	//��һ�п�ʼ��ʽ��ȡ��ÿ����20������
	//��ȡ��ĳ��Ϊ��]�����ȡ����
	//�鿴��һ���Ƿ�Ϊ�գ����ǣ���������������������������̶�ȡ��
};
//������������-------------------------------------------------------------------------------------------------------------
template<typename T>
VECTOR<T>::VECTOR() :size(0), capacity(4096) {
	arr = new T[capacity];
}
template<typename T>
VECTOR<T>::VECTOR(const int s) : size(s), capacity(2 * s) {
	//��ʼ����Ϊ2����С��
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
		cout << "�����±�Խ��" << endl;
	}
}
//�������������������Ա�������忪ʼ---------------------------------------------------------------------------------------
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
		cout << "�±�Խ��" << endl;
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
		cout << "�±�Խ��" << endl;
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
		cerr << "error:�±�Խ��" << endl;
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
		cerr << "error:�±�Խ��" << endl;
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
	out << "VECTOR: ��";
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