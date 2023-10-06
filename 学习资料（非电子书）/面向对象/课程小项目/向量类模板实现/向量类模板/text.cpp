#include"VECTOR.h"
#include<iostream>
#include<conio.h>
VECTOR<int> get_int_data()  // 获取几个样例int数据
{
	VECTOR<int> a;
	for (int i = 0; i < 20; i++) a.push_back(i);
	return a;
}
void t_erase()   // 测试erase函数
{
	cout << "开始erase的测试" << endl;;
	cout << "int:" << endl;;
	VECTOR<int> a = get_int_data();
	cout << "原数组：";
	cout << "a="<<a << endl;
	cout << endl;
	cout << "erase(10, 13)：" << endl;;
	a.erase(10, 13);	
	cout << "a="<<a << endl;
	cout << endl;
	cout << "erase(-15, 10)：" << endl;
	a.erase(-15, 10);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(15, 50)：" << endl;
	a.erase(15, 55);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(2)：" << endl;
	a.erase(2);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(-2)：" << endl;
	a.erase(-2);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(-50)：" << endl;
	a.erase(-50);
	cout << "a=" << a << endl;
	cout << endl;
}
void t_front_back() 
{
	cout << "---------------------------------------------------------" << endl;
	cout << "开始front和back的测试" << endl;;
	VECTOR<int> a = get_int_data();
	cout << "原数组：";
	cout << "a="<<a << endl;
	cout << "正常测试：" << endl;
	cout << "a.front()=" << a.front() << endl;
	cout << "a.back()=" << a.back() << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << "异常测试：";
	VECTOR<int> b;
	cout << "创建一个空向量b" << endl;
	cout << "b=" << b << endl;
	cout << "b.front()=" << b.front() << endl;
	cout << "成功过输出异常处理错误报告！" << endl;
	cout << "b.back()=" << b.back() << endl;
	cout << "成功过输出异常处理错误报告！" << endl;
	cout << endl;
}
void t_input_int() {
	cout << "测试input()函数(从文本中读入):" << endl;
	VECTOR<int> x = get_int_data();
	x.output();
	cout << "创建x向量：" << endl;
	cout << "x=" << x << endl;
	cout << "将向量x写入文件(可在out.txt文件中查看):" << endl;
	cout << "x.output()" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	VECTOR<int> v;
	v.input();
	cout << "用向量v从文件中读入：" << endl;
	cout << "v.input():" << endl;
	cout << "v=" << v << endl;
	cout << endl;
	cout << "运行成功!" << endl;
	cout << endl;
}
void t_get_size_space() {	// 用int型数据测试
	VECTOR<int> v = get_int_data();
	cout << "原向量：" << endl;
	cout << v << endl;
	cout<<endl;
	cout << "测试get_size（）函数：" << endl;
	cout << "v.get_size()=" << v.getsize() << endl;
	if (v.getsize() == 20) cout << "测试成功" << endl;
	else cout << "测试失败" << endl;;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "测试space()函数：" << endl;
	cout << "VECTOR的空间 v.space()=" << v.space() << endl;
	cout << "运行成功" << endl;
	cout << endl;
}
void t_insert() {
	VECTOR<int> v = get_int_data();
	cout << "原数组：" << endl;;
	cout << v << endl;
	cout << endl;
	cout << "在下标5处插入6个666：" << endl;
	cout << "v.insert(666,5,6):" << endl;
	v.insert(666, 5, 6);
	cout << v << endl;
	cout << endl;
	cout << "运行成功！" << endl;
}
void t_pushback_add() {
	VECTOR<int> t1 = get_int_data();
	VECTOR<int> t2 = get_int_data();
	VECTOR<int> t3 = get_int_data();
	VECTOR<int> t4 = get_int_data();
	cout << "获取测试样例t1，t2,t3,t4：" << endl;
	cout << "原t1：" << t1 << endl;
	cout << "原t2：" << t2 << endl;
	cout << "原t3：" << t3 << endl;
	cout << "原t4：" << t4 << endl;
	cout << endl;
	cout << "测试+=运算符：-------------------------------------------------------------------" << endl;
	t2 += t1;
	cout << "t2+=t1:"<<endl;
	cout<<"t2 = "<<t2 << endl;
	cout << "测试+运算符：-------------------------------------------------------------------" << endl;
	t3 = t1 + t4;
	cout << "t3 = t1 + t4" << endl;
	cout<< "t3= "<< t3 << endl;
	cout << "测试reverse函数：---------------------------------------------------------------" << endl;
	t3.reverse();
	cout << "t3.reverse()" << endl;
	cout<<"t3= " << t3 << endl;
	cout << "测试push_back函数：-------------------------------------------------------------" << endl;
	t1.push_back(77);
	cout << "t1.push_back(77):" << endl;
	cout<<"ti= " << t1 << endl;
	cout << endl;
}
void menu()
{
	cout << "\n\n" << endl;
	cout << "===============   VECTOR向量类模板的测试   ====================" << endl;
	cout << "===============================================================" << endl;
	cout << endl;
	cout << "  1 ---- 测试earse函数 ------------------------------------====\n" << endl;
	cout << "  2 ---- 测试获取向量头、尾元素函数 -----------------------====\n" << endl;
	cout << "  3 ---- 测试向量输出与读入到文本 -------------------------====\n" << endl;
	cout << "  4 ---- 测试获取向量大小与空间 ---------------------------====\n" << endl;
	cout << "  5 ---- 测试insert()函数 ---------------------------------====\n" << endl;
	cout << "  6 ---- 测试“+”、“+=”、“reserve”、“push_back”函数 ====\n" << endl;
	cout << "==========================final================================" << endl;
}
int main()
{
	while (true)
	{
		menu();
		char ch = _getch();
		system("cls");
		switch (ch)
		{
		case '1':t_erase(); break;
		case '2':t_front_back(); break;
		case '3':t_input_int(); break;
		case '4':t_get_size_space(); break;
		case '5':t_insert(); break;
		case '6':t_pushback_add(); break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
