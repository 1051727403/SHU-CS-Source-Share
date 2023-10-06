// MyString.h				封装C-字符串

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
	friend int stoi(const MyString& str);				// 将MyString对象转换为int返回
	friend void swap(MyString& str1, MyString& str2); 	// 交换两个MyString
	friend MyString to_MyString(const char str[]); 		// 将C字符串转换为MyString
public:
	MyString(const char* str = "");									// 构造函数
	MyString(const char* str, const size_t n);						// 构造函数
	MyString(const MyString& str);									// （深）拷贝构造函数
	~MyString();													// 析构函数

	MyString& operator=(const MyString& str);						// （深）赋值运算符函数
	char& operator[](const size_t& index);							// 这个方括号运算符函数调用表达式可以做左值
	MyString operator+(const MyString& str) const;					// 两个MyString相加
	MyString& operator+=(const MyString& str);
	bool operator==(const MyString& str) const;						// 判断两个MyString是否相等
	bool operator<(const MyString& str) const;						// 比较两个MyString
	bool operator<=(const MyString& str) const;
	bool operator>(const MyString& str) const;
	bool operator>=(const MyString& str) const;

	void clear();										// 清空MyString
	MyString copy() const;								// 复制一个新的MyString
	size_t size() const;								// 返回MyString长度
	const char* c_str() const;							// 返回MyString的C字符串形式
	bool empty() const;									// 询问MyString是否为空
	MyString& reverse(); 								// 反转整个MyString
	MyString& append(const MyString& str);				// 将str添加到末尾
	MyString& erase(const size_t& index, const size_t& len); 						// 将下标起始于index,长度为len的部分擦除
	MyString& replace(const size_t& index, const size_t& len, const MyString& str); // 将下标起始于index,长度为len的部分替换为str
	MyString& insert(const size_t& index, const size_t& len, const MyString& str);  // 在下标起始于index处插入str,插入的长度为len
	MyString substr(const size_t& index, const size_t& len) const; 					// 返回下标起始于index,长度为len的子串
	void swap(MyString& str); // 交换两个MyString

private:
	char* p;

	static void New(char*& str, const size_t& len);		// 申请长度为len的空间
	static void Free(char*& str);						// 释放空间
};

ostream& operator<<(ostream& out, const MyString& str);
istream& operator>>(istream& in, MyString& str);
istream& getline(istream& in, MyString& str, const char delim = '\n');
int stoi(const MyString& str);
void swap(MyString& str1, MyString& str2);
MyString to_MyString(const char str[]);


#endif
