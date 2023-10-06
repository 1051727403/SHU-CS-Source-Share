#include"String.h"
#include"Vector.h"
//#include<string>
using namespace std;
void test() {
	cout << "����String������������:--------------------------------------------------------------" << endl;
	cout << "ԭ���ݣ�" << endl;
	String a1 = "0123456", a2 = "01234";
	cout << "a1 = " << a1 << "\na2 = " << a2 <<"\n";
	cout << "���ԡ�+�������:" << endl;
	cout << "a1 + a2 = " << a1 + a2 << endl;
	cout << endl;
	cout << "���ԡ�+=���������" << endl;
	cout << "a1 = " << a1 << "\na2 = " << a2 << "\n";
	cout << "a1 += a2 \na1 = " << a1 << "\na2 = " << a2 << endl;
	a1 += a2;
	cout << endl;
	String b1 = "123", b2 = "234";
	cout << "ԭ���ݣ�" << endl;
	cout << "b1=" << b1 << "\nb2=" << b2 << endl;
	cout << "���ԡ�<���������" << endl;
	cout << "b1<b2=" << boolalpha<<(b1 < b2)<< endl;
	cout << "���ԡ�<=���������" << endl;
	cout << "b1<=b2="  << (b1 <= b2) << endl;
	cout << "���ԡ�>���������" << endl;
	cout << "b1>b2="  << (b1 > b2) << endl;
	cout << "���ԡ�>=���������" << endl;
	cout << "b1>=b2="  << (b1 >= b2) << endl;
	cout << "���ԡ�==���������" << endl;
	cout << "b1==b2="   << (b1 == b2) << endl;
	cout << "���ԡ�!=���������" << endl;
	cout << "b1!=b2="  << (b1 != b2) << endl;
	cout << noboolalpha << endl;
	cout << "���ԡ�[]���������" << endl;
	cout << "b1[0]=" << b1[0] << endl;
	cout << "b1[-1]="; b1[-1];
	cout << "b1[100]="; b1[100];
	//cout << (b1 < b2 )<< endl;
}
void test2() {
	cout << "����String���'c_str()'��'copy()'��'replace()'��'substr()'��'stoi()'����:--------------------------------------------------------------" << endl;
	cout << "ԭ���ݣ�" << endl;
	String a1 = "0123456", a2 = "01234";
	cout << "a1 = " << a1 << "\na2 = " << a2 << "\n";
	cout << "����'c_str()'������" << endl;
	cout << "a2.c_str() = " << a2.c_str() << endl;
	cout << "����'copy()'������" << endl;
	a1 = a2.copy();
	cout << "a1 = a2.copy():\n\ta1 = " << a1 << "\n\ta2 = " << a2 << endl;
	cout << "a1.replace(2, 3, a2):\n\ta1 = " << a1.replace(2, 3, a2) << "\n\ta2 = " << a2 << endl;
	cout << "a1.replace(2, 30, a2):\n\ta1 = " << a1.replace(2, 30, a2) << "\n\ta2 = " << a2 << endl;
	cout << "a1.replace(20, 3, a2):\n\ta1 = " << a1.replace(20, 3, a2) << "\n\ta2 = " << a2 << endl;
	cout << "a2.substr(1, 3) = " << a2.substr(1, 3) << endl;
	cout << "a2.substr(1, 10) = " << a2.substr(1, 10) << endl;
	cout << "a2.substr(10, 2) = " << a2.substr(10, 2) << endl;
	cout << "stoi(a2) = " << Stoi(a2) << endl;
	cout << "stoi(a1="") = " << Stoi(a1="") << endl;
	cout << "����putout()����:" << endl;
	cout << "a2.putout()="; a2.putout(cout);
	cout << endl;
	cout << "����putin()����(�ԣ�X1��X2��...,Xn������ʽ����):";
	a2.putin(cin);
	cout << "a2=" << a2 << endl;
}
void test3() {
	cout << "String����ü̳��ڻ���ĺ���------------------------------------------------------------------------------" << endl;
	cout << "ԭ���ݣ�" << endl;
	String a1 = "0123456", a2 = "01234";
	cout << "a1 = " << a1 << "\na2 = " << a2 << "\n";
	cout << "���ԡ�getsize()������:" << endl;
	cout << "a1.getsize()=" << a1.getsize() << endl;
	cout << "���ԡ�insert()������:" << endl;
	a1.insert('1', 3, 1);
	cout << "a1.insert('1',3,1)=" << a1 << endl;
	cout << "���ԡ�erase()������:" << endl;
	a2.erase(0);
	cout << "a2.erase(0)=" << a2 << endl;
	cout << "a2.erase(100)="; a2.erase(100);
	a2.erase(0, 2);
	cout << "a2.erase(0,2)=" << a2 << endl;
	cout << "a2.erase(2,3)="; a2.erase(2, 3);
	cout << "����empty()����:" << endl;
	cout << "a2.empty()=" << a2.empty() << endl;
	cout << "����clear()����:" << endl;
	a2.clear();
	cout <<"a2.clear(),a2.empty()=" <<a2.empty()<< endl;
	cout << "����swap()����:" << endl;
	cout << "a1=" << a1 << "\ta2=" << a2 << endl;
	cout << "a1.swap(a2):" << endl;
	a1.swap(a2);
	cout << "a1=" << a1 << "\ta2=" << a2 << endl;
	cout << "����reverse()����:" << endl;
	a2.reverse();
	cout << "a2.reverse()=" << a2 << endl;

}
void test4()
{
	cout << "����Vector��ĺ���:--------------------------------------------------------------" << endl;
	cout << "ԭ���ݣ�" << endl;
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int arr2[11] = { 0,100,200,300,400,500,600,700,800,900,1000 };
	int arr3[10] = { 9,8,7,6,5,4,3,2,1,0 };
	Vector<int>v1(10, arr);
	Vector<int>v2(11, arr2);
	Vector<int>v3(10, arr3);
	cout << "v1=" << v1 << endl;
	cout << "v2=" << v2 << endl;
	cout << "v3=" << v3 << endl;
	cout << "����assign()����:" << endl;
	cout << "v1.assign(v3):" << endl;
	v1.assign(v3);
	cout << "v1=" << v1 << endl;
	cout << "v3=" << v3 << endl;
	cout << "\n����push_back()����:" << endl;
	v1.push_back(10);
	cout << "v1.push_back(10)=" << v1 << endl;
	cout << "\n����pop_back()����:" << endl;
	Vector<int>v4;
	v1.pop_back();
	cout << "v1.pop_back()=" << v1 << endl;
	cout << "v4=" << v4 << endl;
	cout << "v4.pop_back()=";v4.pop_back();
	cout << "\n����back()����:" << endl;
	cout << "v1.back()=" << v1.back() << endl;
	cout << "v4.back()="; v4.back();
	cout << "\n����'+'���������ͬά��������ӣ�:" << endl;
	cout << "ԭ���ݣ�" << endl;
	cout << "v1=" << v1 << endl;
	cout << "v2=" << v2 << endl;
	cout << "v3=" << v3 << endl;
	cout << endl;
	cout << "v1+v3=" << v1 + v3 << endl;
	cout << "v1+v2=";v1 + v2;
	cout << "v4+v4=" << v4 + v4 << endl;
	cout << "v1+=v3:" << endl;
	v1 += v3;
	cout << "v1=" << v1 << endl;
	cout << "v3=" << v3 << endl;
	cout << "v1+=v2:"; v1 += v2;
	cout << "����putout()����:" << endl;
	cout << "v1.putout()="; v1.putout(cout);
	cout << endl;
	cout << "����putin()����(�ԣ�X1��X2��...,Xn������ʽ����):";
	v1.putin(cin);
	cout << "v1="<<v1 << endl;
}
void test5() {
	cout << "Vector����ü̳��ڻ���ĺ���------------------------------------------------------------------------------" << endl;
	cout << "ԭ���ݣ�" << endl;
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int arr2[11] = { 0,100,200,300,400,500,600,700,800,900,1000 };
	int arr3[10] = { 9,8,7,6,5,4,3,2,1,0 };
	Vector<int>v1(10, arr);
	Vector<int>v2(11, arr2);
	Vector<int>v3(10, arr3);
	cout << "v1=" << v1 << endl;
	cout << "v2=" << v2 << endl;
	cout << "v3=" << v3 << endl;
	cout << "���ԡ�getsize()������:" << endl;
	cout << "v1.getsize()=" << v1.getsize() << endl;
	cout << "���ԡ�insert()������:" << endl;
	v1.insert(1, 3, 1);
	cout << "v1.insert('1',3,1)=" << v1 << endl;
	cout << "���ԡ�erase()������:" << endl;
	v2.erase(0);
	cout << "v2.erase(0)=" << v2 << endl;
	cout << "v2.erase(100)="; v2.erase(100);
	v2.erase(0, 2);
	cout << "v2.erase(0,2)=" << v2 << endl;
	cout << "v2.erase(2,100)="; v2.erase(2, 100);
	cout << "����empty()����:" << endl;
	cout << "v2.empty()=" << v2.empty() << endl;
	cout << "����clear()����:" << endl;
	v2.clear();
	cout << "v2.clear(),v2.empty()=" << v2.empty() << endl;
	cout << "����swap()����:" << endl;
	cout << "v1=" << v1 << "\tv2=" << v2 << endl;
	cout << "v1.swap(v2):" << endl;
	v1.swap(v2);
	cout << "v1=" << v1 << "\tv2=" << v2 << endl;
	cout << "����reverse()����:" << endl;
	v2.reverse();
	cout << "v2.reverse()=" << v2 << endl;
}

int main()
{
	Vector<int>v;
	//test();
	//test2();
	//test3();
	//test4();
	test5();


	return 0;
}