// MyStringTesting.cpp	测试函数
#include "MyString.h"
#include <cstdio>
#include <stdlib.h>

void test_jc()
{
	cout << "-------------------------------------------" << endl;
	cout << "A.测试字符串操作函数" << endl;
	MyString s("123"), s1("456"), s2("789"), s3("147"), s4("258"), s5("369");
	cout << "-------------------------------------------" << endl;
	cout << "C-str()" << endl;
	const char* t = s.c_str();
	cout << "s转c字符串" << endl;
	cout << t << endl;

	cout << "-------------------------------------------" << endl;
	cout << "reverse()" << endl;
	cout << "s1 = " << s1 << endl;
	s1.reverse();
	cout << "s1.reverse() = " << s1 << endl;

	cout << "-------------------------------------------" << endl;
	cout << "erase()" << endl;
	cout << "s2 = " << s2 << endl;
	s2.erase(1, 2);
	cout << "s2.erase(1, 2) = " << s2 << endl;

	cout << "-------------------------------------------" << endl;
	cout << "insert()" << endl;
	cout << "s3 = " << s3 << endl;
	s3.insert(1, 2, s);
	cout << "s3.insert(1, 2, s) = " << s3 << endl;

	cout << "-------------------------------------------" << endl;
	cout << "replace()" << endl;
	cout << "s4 = " << s4 << endl;
	s4.replace(1, 2, s);
	cout << "s4.replace(1, 2, s) = " << s4 << endl;

	cout << "-------------------------------------------" << endl;
	cout << "substr()" << endl;
	cout << "s5 = " << s5 << endl;
	cout << "s5.substr(1, 2) = " << s5.substr(1, 2) << endl;
	cout << "\n\n";
	system("pause");
}

void test_ldw()
{
	cout << "-------------------------------------------" << endl;
	cout << "B.测试运算符" << endl;
	cout << "-------------------------------------------" << endl;
	MyString str, str2, str3, str4, str5;
	str = "00000", str2 = "11111", str3 = "22222", str4 = "33333", str5 = "12345";
	cout << "str=" << str << endl;
	cout << "str2=" << str2 << endl;
	cout << "str3=" << str3 << endl;
	cout << "str4=" << str4 << endl;
	cout << "str5=" << str5 << endl;
	cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << "operator+()" << endl;
	cout << "测试+运算符：" << endl;
	cout << "str + str2 = " << str << " + " << str2 << " = " << str + str2 << endl;
	cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << "operator+=()" << endl;
	cout << "测试+=运算符：" << endl;
	str4 += str;
	cout << "(str4 += str) = " << str4 << endl;
	cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << "operator[]()" << endl;
	cout << "测试operator[]运算符：" << endl;
	cout << "str5[0]=" << str5[0] << endl;
	cout << "str5[1]=" << str5[1] << endl;
	cout << "str5[2]=" << str5[2] << endl;
	cout << "str5[3]=" << str5[3] << endl;
	cout << "str5[4]=" << str5[4] << endl;
	cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << "测试swap1：" << endl;
	cout << "str = " << str << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str.swap(str2)后:" << endl;
	str.swap(str2);
	cout << "str = " << str << endl;
	cout << "str2 = " << str2 << endl;
	cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << "测试swap2：" << endl;
	cout << "str = " << str << endl;
	cout << "str2 = " << str2 << endl;
	cout << "swap(str,str2)后:" << endl;
	swap(str, str2);
	cout << "str = " << str << endl;
	cout << "str2 = " << str2 << endl;
	system("pause");
}

void test_sq() {			//测试to_MyString, copy
	cout << "-------------------------------------------" << endl;
	cout << "C.测试拷贝函数" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "to_MyString" << endl;
	char test1[32] = "test to_MyString function";
	cout << "tp_MyString(test1) = " << to_MyString(test1) << endl;

	cout << "-------------------------------------------" << endl;
	cout << "copy()" << endl;
	char test2[32] = "test copy function";
	MyString my_obj(test2);
	cout << "my_obj.copy() = " << my_obj.copy() << endl;

	printf("my_obj is empty: %d, size is %d\n", my_obj.empty(), my_obj.size());
	system("pause");
}

void test_zry()
{
	MyString s("123"), s1("456"), s2("789"), s3("147"), s4("858"), s5("369");

	cout << "-------------------------------------------" << endl;
	cout << "D.测试运算符重载" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "operator==()" << endl;
	cout << " s2：" << s2 << " s3：" << s3 << endl;
	cout << "比较s2 s3是否相等，测试==运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 == s3) << endl;
	cout << endl;

	cout << " s2：" << s2 << " s4：" << s4 << endl;
	cout << "比较s2 s4是否相等，测试==运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 == s4) << endl;
	cout << endl;

	cout << "-------------------------------------------" << endl;
	cout << "operator<()" << endl;
	cout << " s2：" << s2 << " s3：" << s3 << endl;
	cout << "比较s2是否<s3，测试<运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 < s3) << endl;
	cout << endl;

	cout << " s2：" << s2 << " s4：" << s4 << endl;
	cout << "比较s2是否<s4，测试<运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 < s4) << endl;
	cout << endl;

	cout << "-------------------------------------------" << endl;
	cout << "operator<=()" << endl;
	cout << " s2：" << s2 << " s3：" << s3 << endl;
	cout << "比较s2是否<=s3，测试<=运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 <= s4) << endl;
	cout << endl;

	cout << " s2：" << s2 << " s5：" << s5 << endl;
	cout << "比较s2是否<=s5，测试<=运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 <= s5) << endl;
	cout << endl;

	cout << "-------------------------------------------" << endl;
	cout << "operator>()" << endl;
	cout << " s2：" << s2 << " s3：" << s3 << endl;
	cout << "比较s2是否>s3，测试>运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 > s3) << endl;
	cout << endl;

	cout << " s2：" << s2 << " s5：" << s5 << endl;
	cout << "比较s2是否>s5，测试>运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 > s5) << endl;
	cout << endl;

	cout << "-------------------------------------------" << endl;
	cout << "operator>=()" << endl;
	cout << " s2：" << s2 << " s3：" << s3 << endl;
	cout << "比较s2是否>=s3，测试>=运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 >= s3) << endl;
	cout << endl;

	cout << " s2：" << s2 << " s4：" << s4 << endl;
	cout << "比较s2是否>=s4，测试>=运算符重载：1是，0否" << endl;
	cout << "结果：" << (s2 >= s4) << endl;
	cout << endl;


	system("pause");
}

void test_yjr()
{
	cout << "-------------------------------------------" << endl;
	cout << "E.异常测试" << endl;
	cout << "-------------------------------------------" << endl;
	MyString str1 = "01234", str2 = "01234", str3 = "01234", str4 = "01234", str5 = "01234", str6 = "01234";
	cout << "str1 = str2 = str3 = str4 = str5 = str6 = 01234" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "erase()" << endl;
	cout << "str1.erase(2, 10) = ";
	cout << str1.erase(2, 10) << endl;
	cout << "str2.erase(7, 2) = ";
	cout << str2.erase(7, 2) << endl;

	cout << "-------------------------------------------" << endl;
	cout << "insert()" << endl;
	cout << "str3.insert(7, 2, str4) = ";
	cout << str3.insert(7, 2, str4) << endl;
	cout << "str3.insert(2, 7, str4) = ";
	cout << str3.insert(2, 7, str4) << endl;

	cout << "-------------------------------------------" << endl;
	cout << "replace()" << endl;
	cout << "str4.replace(7, 2, str5) = ";
	cout << str4.replace(7, 2, str5) << endl;
	cout << "str4.replace(2, 7, str5) = ";
	cout << str4.replace(2, 7, str5) << endl;

	cout << "-------------------------------------------" << endl;
	cout << "substr()" << endl;
	cout << "str5.substr(7, 2) = ";
	cout << str5.substr(7, 2) << endl;
	cout << "str5.substr(2, 7) = ";
	cout << str5.substr(2, 7) << endl;

	try {
		cout << "-------------------------------------------" << endl;
		cout << "operator[]()" << endl;
		cout << "str6[7] = ";
		cout << str6[7] << endl;
	}
	catch (int e) {
	}
	cout << endl;
	system("pause");
}

int main()
{
	test_jc();
	system("cls");
	test_ldw();
	system("cls");
	test_sq();
	system("cls");
	test_zry();
	system("cls");
	test_yjr();
	system("cls");
	return 0;
}

