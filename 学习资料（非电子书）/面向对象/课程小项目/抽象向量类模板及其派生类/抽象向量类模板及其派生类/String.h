// String.h
#pragma once
#ifndef STRING_H
#define STRING_H
#include "Cxxll.h"
using namespace std;
// String---------------------------------------------------------
class  String :public Cxxll<char>
{
	friend ostream& operator<<(ostream& out, const String& str);//��string��ʽ���
	friend istream& operator>>(istream& in, String& str);//��string��ʽ����
	friend istream& getline(istream& in, String& str, const char delim);
	friend istream& getline(istream& in, String& Str, int n, char delim);
	friend int Stoi(const String &str);
public:
	String(const char* str="");											// ���캯��
	const char* c_str() const;//���������char������ʽ
	String copy() const;//����ĸ���
	String& replace(const unsigned  int& index, const unsigned int& len, const String& str);//���±�index��ʼlen�����ַ����滻Ϊstr
	String substr(const unsigned int& index, const unsigned int& len) const;//�����±�index��ʼlen���ȵ��ַ���
	String operator+(const String& str)const;//�ڱ��ַ��������s
	String& operator+=(const String& str);//ͬ�ϣ�ע���Լ�	
	bool operator<(const String& str) const;	//���ֵ���Ƚϱ��ַ�����str�Ĵ�С				
	bool operator<=(const String& str) const;
	bool operator>(const String& str) const;
	bool operator>=(const String& str) const;
	bool operator==(const String& str)const;
	bool operator!=(const String& str)const;
	void putout(ostream& out)const;//�ַ�֮���޿ո����
	void putin(istream& in);//���ַ�������
};


#endif