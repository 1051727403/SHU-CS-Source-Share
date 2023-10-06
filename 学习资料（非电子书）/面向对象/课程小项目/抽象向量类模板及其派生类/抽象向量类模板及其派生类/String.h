// String.h
#pragma once
#ifndef STRING_H
#define STRING_H
#include "Cxxll.h"
using namespace std;
// String---------------------------------------------------------
class  String :public Cxxll<char>
{
	friend ostream& operator<<(ostream& out, const String& str);//按string方式输出
	friend istream& operator>>(istream& in, String& str);//按string方式输入
	friend istream& getline(istream& in, String& str, const char delim);
	friend istream& getline(istream& in, String& Str, int n, char delim);
	friend int Stoi(const String &str);
public:
	String(const char* str="");											// 构造函数
	const char* c_str() const;//返回自身的char数组形式
	String copy() const;//自身的副本
	String& replace(const unsigned  int& index, const unsigned int& len, const String& str);//从下标index开始len长度字符串替换为str
	String substr(const unsigned int& index, const unsigned int& len) const;//返回下标index开始len长度的字符串
	String operator+(const String& str)const;//在本字符串后加上s
	String& operator+=(const String& str);//同上，注意自加	
	bool operator<(const String& str) const;	//按字典序比较本字符串和str的大小				
	bool operator<=(const String& str) const;
	bool operator>(const String& str) const;
	bool operator>=(const String& str) const;
	bool operator==(const String& str)const;
	bool operator!=(const String& str)const;
	void putout(ostream& out)const;//字符之间无空格输出
	void putin(istream& in);//按字符串输入
};


#endif