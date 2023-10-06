// String---------------------------------------------------------
#include"String.h"
// �����๹�캯��
//�Ĵ��������
//-----------------------------------------------------------------------------------------------------
String::String(const char* str) : Cxxll<char>(strlen(str), str) {}
void String::putout(ostream& out)const {
	for (int i = 0; i < this->size; i++) {
		cout << this->head[i] << " ";
	}
}

void String::putin(istream& in) {
	const int M = 1024, N = 1;//1024;	// Nȡ��Сֵ1��Ϊ�˵��ԣ�ʵ��ʹ��ʱȡ1024
	String temp;
	char str[M], ch;				// ch��ʼ��Ϊһ����')'�ַ�����
	char buffer[N];
	int i, j, k;

	in.getline(str, M, '(');		// ���˵�'('��֮ǰ�������ַ�
	while (true)						// ���˵���Բ����֮��Ŀհ��ַ�
	{
		ch = in.peek();				// ͵����һ���ַ������Ƿ�Ϊ�հ��ַ�
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			in.get(ch);				// ���ǿհ��ַ�������˵�������ȡ���ã�
		else
			break;					// ֱ�������ǿհ��ַ���������whileѭ��
	}

	if (in.peek() == ')')				// ͵����һ���ַ�������')'
	{
		this->resize(0);			// ���������ά�����ó� 0 ά
		in.get(ch);					// ��ȡ')'��ֹ����Ƕ��ʱ����
		return;						// �˳�������������Ϊ 0 ά����
	}

	for (k = 0; ch != ')'; k++)
	{
		for (i = 0; i < N && ch != ')'; i++)
			in >> buffer[i] >> ch;
		temp.resize(k * N + i);			// ������resize������"����������ԭ������"�Ĺ���
		for (j = 0; j < i; j++)
			temp[k * N + j] = buffer[j];// �����˷����������
	}
	*this = temp;					// �����˸�ֵ��������ֵ���㣩
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
		cerr << "�±�Խ�磻";
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
		cerr << "�±�Խ��";
		return String("");
	}
}

bool String::operator<(const String& str) const {//���ֵ���Ƚϱ��ַ�����str�Ĵ�С	
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

