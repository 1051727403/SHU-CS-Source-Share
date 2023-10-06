// MyString.cpp					成员函数及普通C++函数定义
#include "MyString.h"


MyString::MyString(const char* str)
{
	size_t lenth = strlen(str);
	p = new char;
	New(p, lenth + 1);
	strncpy_s(p, lenth + 1, str, lenth);
	p[lenth] = '\0';
}

MyString::MyString(const char* str, const size_t n)
{
	size_t lenth = min(strlen(str), n);
	p = new char;
	New(p, lenth + 1);
	strncpy_s(p, lenth + 1, str, lenth);
	p[lenth] = '\0';
}

MyString::MyString(const MyString& str)
{
	size_t lenth = strlen(str.p);
	p = new char;
	New(p, lenth + 1);
	strncpy_s(p, lenth + 1, str.p, lenth);
	p[lenth] = '\0';
}

MyString::~MyString()
{
	Free(p);
	p = NULL;
}

MyString& MyString::operator=(const MyString& str)
{
	if (p == str.p) return *this;
	clear();
	size_t lenth = strlen(str.p);
	New(p, lenth + 1);
	strncpy_s(p, lenth + 1, str.p, lenth);
	p[lenth] = '\0';
	return *this;
}

char& MyString::operator[](const size_t& index)
{
	size_t len = strlen(p);
	if (index < 0 || index >= len)
	{
		cerr << "下标越界；";
		throw(-1);
	}
	return p[index];
}

MyString MyString::operator+(const MyString& str) const
{
	size_t len1 = strlen(p), len2 = strlen(str.p);
	size_t len = len1 + len2;
	char* temp = NULL;
	New(temp, len + 1);
	strncpy_s(temp, len + 1, p, len1);
	strncpy_s(temp + len1, len2 + 1, str.p, len2);
	temp[len] = '\0';
	MyString s(temp);
	Free(temp);
	return s;
}

MyString& MyString::operator+=(const MyString& str)
{
	size_t len1 = strlen(p), len2 = strlen(str.p);
	size_t len = len1 + len2;
	char* temp = p;
	p = new char[len + 1];
	strncpy_s(p, len + 1, temp, len1);
	strncpy_s(p + len1, len2 + 1, str.p, len2);
	p[len] = '\0';
	Free(temp);
	return *this;
}

bool MyString::operator==(const MyString& str) const
{
	return !strcmp(p, str.p);
}

bool MyString::operator<(const MyString& str) const
{
	bool istrue = 0;
	if (strcmp(p, str.p) < 0) {
		istrue = 1;
	}
	return istrue;
}

bool MyString::operator<=(const MyString& str) const
{
	bool istrue = 0;
	if (strcmp(p, str.p) <= 0) {
		istrue = 1;
	}
	return istrue;
}

bool MyString::operator>(const MyString& str) const
{
	bool istrue = 0;
	if (strcmp(p, str.p) > 0) {
		istrue = 1;
	}
	return istrue;
}

bool MyString::operator>=(const MyString& str) const
{
	bool istrue = 0;
	if (strcmp(p, str.p) >= 0) {
		istrue = 1;
	}
	return istrue;
}

MyString MyString::copy() const
{
	return MyString(p);
}

size_t MyString::size() const
{
	if (p) return strlen(p);
	return 0;
}

void MyString::clear()
{
	New(p, 1);
	*p = '\0';
}

const char* MyString::c_str() const
{
	size_t len = size();
	char* tp = NULL;
	New(tp, len + 1);
	const char* ans = tp;
	for (char* it = p; len; *(tp++) = *(it++), len--) if (*it == '\0') break;
	tp[len] = '\0';
	return ans;
}

bool MyString::empty() const
{
	return p && strlen(p) == 0 ? true : false;
}

MyString& MyString::reverse()
{
	size_t len = size();
	char* tp = NULL;
	New(tp, len + 1);
	strncpy_s(tp, len + 1, p, len);
	for (size_t i = 0; i < len; ++i) p[i] = tp[len - i - 1];
	p[len] = '\0';
	Free(tp);
	return *this;
}

MyString& MyString::append(const MyString& str)
{
	size_t len = size();
	insert(len, str.size(), str);
	return *this;
}

MyString& MyString::erase(const size_t& index, const size_t& len)
{
	size_t tlen = size();
	try {
		if (index >= tlen) throw - 1;
		if (tlen <= len + index) {
			char* tp = NULL;
			New(tp, index + 1);
			for (size_t i = 0; i < index; ++i) tp[i] = p[i];
			tp[index] = '\0';
			Free(p);
			p = tp;
			return *this;
		}
		char* tp = NULL;
		New(tp, tlen - len + 1);
		for (size_t i = 0; i < index; ++i) tp[i] = p[i];
		for (size_t i = index + len; i < tlen; ++i) tp[i - len] = p[i];
		tp[tlen - len] = '\0';
		Free(p);
		p = tp;
	}
	catch (int e) {
		cerr << "删除子串时下标异常；";
	}
	return *this;
}

MyString& MyString::replace(const size_t& index, const size_t& len, const MyString& str)
{
	erase(index, len);
	return insert(index, str.size(), str);
}

MyString& MyString::insert(const size_t& index, const size_t& len, const MyString& str)
{
	size_t tlen = size();
	char* tp = NULL;
	size_t lenth = min(str.size(), len);
	New(tp, tlen + lenth + 1);
	try {
		if (index > tlen) throw - 1;
		for (size_t i = 0; i < index; ++i) tp[i] = p[i];
	}
	catch (int e) {
		Free(tp);
		cerr << "插入MyString时下标越界；";
		return *this;
	}
	for (size_t i = index; i < index + lenth; ++i) tp[i] = str.p[i - index];
	for (size_t i = index + lenth; i < tlen + lenth; ++i) tp[i] = p[i - lenth];
	tp[tlen + lenth] = '\0';
	Free(p);
	p = tp;
	return *this;
}

MyString MyString::substr(const size_t& index, const size_t& len) const
{
	char* t_char = NULL;
	try {
		if (index >= size()) throw 1.0;
		else if (index + len > size()) throw - 1;
		New(t_char, len + 1);
		for (size_t i = index; i < index + len; ++i)
			t_char[i - index] = p[i];
		t_char[len] = '\0';
	}
	catch (int e) {
		size_t tlen = size();
		New(t_char, tlen - index + 1);
		for (size_t i = index; i < tlen; ++i)
			t_char[i - index] = p[i];
		t_char[tlen - index] = '\0';
	}
	catch (double e) {
		t_char = new char;
		t_char[0] = '\0';
		cerr << "非法下标输入；";
	}
	MyString t(t_char);
	Free(t_char);
	return t;
}

void MyString::New(char*& str, const size_t& len)
{
	Free(str);
	str = new char[len];
}

void MyString::Free(char*& str)
{
	if (str) delete[] str;
}

void MyString::swap(MyString& str)
{
	char* t = p;
	p = str.p;
	str.p = t;
}

int stoi(const MyString& str)
{
	int sum = 0, flag = 1;
	try {
		size_t len = strlen(str.p), i = 0;
		if (!len) throw - 1;
		if (str.p[0] == '-')
		{
			flag = -1;
			i = 1;
		}
		for (; i < len; i++) {
			if (str.p[i] < '0' || str.p[i] > '9') throw - 1;
			sum = sum * 10 + str.p[i] - '0';
		}
	}
	catch (int e) {
		cerr << "无法转换该字符串为int；";
	}
	return flag * sum;
}

void swap(MyString& str1, MyString& str2)
{
	char* t = str1.p;
	str1.p = str2.p;
	str2.p = t;
}

MyString to_MyString(const char str[])
{
	return MyString(str);
}

ostream& operator<<(ostream& out, const MyString& str)
{
	return out << str.p;
}

istream& operator>>(istream& in, MyString& str)
{
	size_t lenth = 8, now = 0;
	char* temp = NULL, t;
	MyString::New(temp, lenth);
	do {
		t = in.get();
		temp[now++] = t;
		if (now == lenth)
		{
			lenth *= 2;
			char* tt = temp;
			temp = new char[lenth];
			strncpy_s(temp, lenth, tt, lenth / 2);
			MyString::Free(tt);
		}
	} while (t != '\n' && t != ' ');
	MyString::New(str.p, now + 1);
	strncpy_s(str.p, now + 1, temp, now);
	str.p[now] = '\0';
	MyString::Free(temp);
	return in;
}

istream& getline(istream& in, MyString& str, const char delim)
{
	size_t lenth = 2, now = 0;
	char* temp = NULL, t;
	MyString::New(temp, lenth);
	do {
		t = in.get();
		temp[now++] = t;
		if (now == lenth)
		{
			lenth *= 2;
			char* tt = temp;
			temp = new char[lenth];
			strncpy_s(temp, lenth, tt, lenth / 2);
			MyString::Free(tt);
		}
	} while (t != delim);
	MyString::New(str.p, now + 1);
	strncpy_s(str.p, now + 1, temp, now);
	str.p[now] = '\0';
	MyString::Free(temp);
	return in;
}

