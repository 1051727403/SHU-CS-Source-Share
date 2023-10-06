// MyString.h				��װC-�ַ���

#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
	friend ostream& operator<<(ostream& out, const MyString& str);
	friend istream& operator>>(istream& in, MyString& str);
	friend istream& getline(istream& in, MyString& str, const char delim);
	friend int stoi(const MyString& str);				// ��MyString����ת��Ϊint����
	friend void swap(MyString& str1, MyString& str2); 	// ��������MyString
	friend MyString to_MyString(const char str[]); 		// ��C�ַ���ת��ΪMyString
public:
	MyString(const char* str = "");									// ���캯��
	MyString(const char* str, const size_t n);						// ���캯��
	MyString(const MyString& str);									// ����������캯��
	~MyString();													// ��������

	MyString& operator=(const MyString& str);						// �����ֵ���������
	char& operator[](const size_t& index);							// ���������������������ñ��ʽ��������ֵ
	MyString operator+(const MyString& str) const;					// ����MyString���
	MyString& operator+=(const MyString& str);
	bool operator==(const MyString& str) const;						// �ж�����MyString�Ƿ����
	bool operator<(const MyString& str) const;						// �Ƚ�����MyString
	bool operator<=(const MyString& str) const;
	bool operator>(const MyString& str) const;
	bool operator>=(const MyString& str) const;

	void clear();										// ���MyString
	MyString copy() const;								// ����һ���µ�MyString
	size_t size() const;								// ����MyString����
	const char* c_str() const;							// ����MyString��C�ַ�����ʽ
	bool empty() const;									// ѯ��MyString�Ƿ�Ϊ��
	MyString& reverse(); 								// ��ת����MyString
	MyString& append(const MyString& str);				// ��str��ӵ�ĩβ
	MyString& erase(const size_t& index, const size_t& len); 						// ���±���ʼ��index,����Ϊlen�Ĳ��ֲ���
	MyString& replace(const size_t& index, const size_t& len, const MyString& str); // ���±���ʼ��index,����Ϊlen�Ĳ����滻Ϊstr
	MyString& insert(const size_t& index, const size_t& len, const MyString& str);  // ���±���ʼ��index������str,����ĳ���Ϊlen
	MyString substr(const size_t& index, const size_t& len) const; 					// �����±���ʼ��index,����Ϊlen���Ӵ�
	void swap(MyString& str); // ��������MyString

private:
	char* p;

	static void New(char*& str, const size_t& len);		// ���볤��Ϊlen�Ŀռ�
	static void Free(char*& str);						// �ͷſռ�
};

ostream& operator<<(ostream& out, const MyString& str);
istream& operator>>(istream& in, MyString& str);
istream& getline(istream& in, MyString& str, const char delim = '\n');
int stoi(const MyString& str);
void swap(MyString& str1, MyString& str2);
MyString to_MyString(const char str[]);


#endif
