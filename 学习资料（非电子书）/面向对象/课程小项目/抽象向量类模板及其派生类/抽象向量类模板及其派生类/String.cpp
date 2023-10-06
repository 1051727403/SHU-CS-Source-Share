// String---------------------------------------------------------
#include"String.h"
// 派生类构造函数
//四大基本函数
//-----------------------------------------------------------------------------------------------------
String::String(const char* str) : Cxxll<char>(strlen(str), str) {}
void String::putout(ostream& out)const {
	for (int i = 0; i < this->size; i++) {
		cout << this->head[i] << " ";
	}
}

void String::putin(istream& in) {
	const int M = 1024, N = 1;//1024;	// N取最小值1是为了调试，实际使用时取1024
	String temp;
	char str[M], ch;				// ch初始化为一个非')'字符即可
	char buffer[N];
	int i, j, k;

	in.getline(str, M, '(');		// 过滤掉'('及之前的所有字符
	while (true)						// 过滤掉左圆括号之后的空白字符
	{
		ch = in.peek();				// 偷看下一个字符，看是否为空白字符
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			in.get(ch);				// 若是空白字符，则过滤掉（即读取后不用）
		else
			break;					// 直到遇到非空白字符，结束本while循环
	}

	if (in.peek() == ')')				// 偷看下一个字符，若是')'
	{
		this->resize(0);			// 将本对象的维数设置成 0 维
		in.get(ch);					// 读取')'防止向量嵌套时出错
		return;						// 退出本函数，输入为 0 维向量
	}

	for (k = 0; ch != ')'; k++)
	{
		for (i = 0; i < N && ch != ')'; i++)
			in >> buffer[i] >> ch;
		temp.resize(k * N + i);			// 利用了resize函数的"尽量保留了原有数据"的功能
		for (j = 0; j < i; j++)
			temp[k * N + j] = buffer[j];// 利用了方括号运算符
	}
	*this = temp;					// 利用了赋值运算符（深赋值运算）
};

// 49 Pineklll getline
istream& getline(istream& in, String& str, int n=1, const char delim = '\n') {
	if (n <= 0) return in;
	char* p = new char[n];
	in.getline(p, n, delim);
	str = p;
	delete[]p;
	return in;
};
String String::operator+(const String& str) const
{
	int lenth = size + str.size;
	char* temp = new char[lenth + 1];
	for (int i = 0; i < size; i++) temp[i] = head[i];
	for (int i = size; i < lenth; i++) temp[i] = str.head[i-size];
	temp[lenth] = '\0';
	String res(temp);
	delete[] temp;
	return res;
}
String& String::operator+=(const String& str)
{
	int lenth = size + str.size;
	const char* temp = head;
	head = new char[lenth+1];
	strncpy_s(head, lenth + 1, temp, size);
	strncpy_s(head + size, lenth - size + 1, str.head, str.size);
	head[lenth] = '\0';
	if (temp) delete[] temp;
	return *this;
}
const char* String::c_str() const
{
	char* t = new char[size + 1];
	strncpy_s(t, size + 1, head, size);
	t[size] = '\0';
	return t;
}
String String::copy() const
{
	return String(*this);
}
String& String::replace(const unsigned int& index, const unsigned int& len, const String& str)
{
	int lenth1 = size, lenth2 = str.size;
	try {
		if (index >= lenth2) throw - 1;
		int dellen = min(len, lenth1 - index);
		char* res = new char[lenth1 - dellen + lenth2 + 1];
		strncpy_s(res, lenth1 - dellen + lenth2 + 1, head, index);
		strncpy_s(res + index, lenth1 - dellen + lenth2 + 1 - index, str.head, lenth2);
		strncpy_s(res + index + lenth2, lenth1 - dellen + 1 - index, head + index + dellen, lenth1 - dellen - index);
		res[lenth1 - dellen + lenth2] = '\0';
		delete[] head;
		head = res;
	}
	catch (int e) {
		cerr << "下标越界；";
	}
	return *this;
}
String String::substr(const unsigned int& index, const unsigned int& len) const
{
	int lenth = size;
	try {
		if (index + len >= lenth) throw - 1;
		char* t = new char[len + 1];
		for (int i = index; i < index + len; i++)
			t[i - index] = head[i];
		t[len] = '\0';
		return String(t);
	}
	catch (int e) {
		cerr << "下标越界";
		return String("");
	}
}

bool String::operator<(const String& str) const {//按字典序比较本字符串和str的大小	
	return strcmp(head, str.head) < 0;
};				
bool String::operator<=(const String& str) const {
	return *this < str || *this == str;
};
bool String::operator>(const String& str) const {
	return strcmp(head, str.head) > 0;
};
bool String::operator>=(const String& str) const {
	return *this > str || *this == str;
};
bool String::operator==(const String& str)const {
	return strcmp(head, str.head) == 0;
};
bool String::operator!=(const String& str)const {
	return strcmp(head, str.head) != 0;
};
ostream& operator<<(ostream& out, const String& str)
{
	for (int i = 0; i < str.size; i++)
		out << str.head[i];
	return out;
}
istream& operator>>(istream& in, String& str)
{
	char* t = new char[8];
	size_t lenth = 0, max_lenth = 8;
	while ((t[lenth] = in.get()) != ' ' && t[lenth] != '\n')
		if (++lenth == max_lenth)
		{
			char* temp = new char[max_lenth <<= 1];
			strncpy_s(temp, max_lenth, t, lenth);
			char* del = t;
			t = temp;
			delete[] del;
		}
	if (lenth < max_lenth)
	{
		char* temp = new char[lenth + 1];
		strncpy_s(temp, lenth + 1, t, lenth);
		char* del = t;
		t = temp;
		delete[] del;
	}
	str.head = t;
	return in;
}
istream& getline(istream& in, String& str, const char delim = '\n')
{
	char* t = new char[8];
	size_t lenth = 0, max_lenth = 8;
	while ((t[lenth] = in.get()) != delim)
		if (++lenth == max_lenth)
		{
			char* temp = new char[max_lenth <<= 1];
			strncpy_s(temp, max_lenth, t, lenth);
			char* del = t;
			t = temp;
			delete[] del;
		}
	if (lenth < max_lenth)
	{
		char* temp = new char[lenth + 1];
		strncpy_s(temp, lenth + 1, t, lenth);
		char* del = t;
		t = temp;
		delete[] del;
	}
	str.head = t;
	return in;
}
int Stoi(const String &str)
{
	int res = 0, flag = 1, idx = 0;
	if (str.head[0] == '-')
	{
		flag = -1;
		idx = 1;
	}
	while (str.head[idx] >= '0' && str.head[idx] <= '9')
		res = res * 10 + str.head[idx++] - '0';
	return res * flag;
}


// String---------------------------------------------------------

