#include"VECTOR.h"
#include<iostream>
#include<conio.h>
VECTOR<int> get_int_data()  // ��ȡ��������int����
{
	VECTOR<int> a;
	for (int i = 0; i < 20; i++) a.push_back(i);
	return a;
}
void t_erase()   // ����erase����
{
	cout << "��ʼerase�Ĳ���" << endl;;
	cout << "int:" << endl;;
	VECTOR<int> a = get_int_data();
	cout << "ԭ���飺";
	cout << "a="<<a << endl;
	cout << endl;
	cout << "erase(10, 13)��" << endl;;
	a.erase(10, 13);	
	cout << "a="<<a << endl;
	cout << endl;
	cout << "erase(-15, 10)��" << endl;
	a.erase(-15, 10);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(15, 50)��" << endl;
	a.erase(15, 55);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(2)��" << endl;
	a.erase(2);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(-2)��" << endl;
	a.erase(-2);
	cout << "a=" << a << endl;
	cout << endl;
	cout << "erase(-50)��" << endl;
	a.erase(-50);
	cout << "a=" << a << endl;
	cout << endl;
}
void t_front_back() 
{
	cout << "---------------------------------------------------------" << endl;
	cout << "��ʼfront��back�Ĳ���" << endl;;
	VECTOR<int> a = get_int_data();
	cout << "ԭ���飺";
	cout << "a="<<a << endl;
	cout << "�������ԣ�" << endl;
	cout << "a.front()=" << a.front() << endl;
	cout << "a.back()=" << a.back() << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << "�쳣���ԣ�";
	VECTOR<int> b;
	cout << "����һ��������b" << endl;
	cout << "b=" << b << endl;
	cout << "b.front()=" << b.front() << endl;
	cout << "�ɹ�������쳣������󱨸棡" << endl;
	cout << "b.back()=" << b.back() << endl;
	cout << "�ɹ�������쳣������󱨸棡" << endl;
	cout << endl;
}
void t_input_int() {
	cout << "����input()����(���ı��ж���):" << endl;
	VECTOR<int> x = get_int_data();
	x.output();
	cout << "����x������" << endl;
	cout << "x=" << x << endl;
	cout << "������xд���ļ�(����out.txt�ļ��в鿴):" << endl;
	cout << "x.output()" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	VECTOR<int> v;
	v.input();
	cout << "������v���ļ��ж��룺" << endl;
	cout << "v.input():" << endl;
	cout << "v=" << v << endl;
	cout << endl;
	cout << "���гɹ�!" << endl;
	cout << endl;
}
void t_get_size_space() {	// ��int�����ݲ���
	VECTOR<int> v = get_int_data();
	cout << "ԭ������" << endl;
	cout << v << endl;
	cout<<endl;
	cout << "����get_size����������" << endl;
	cout << "v.get_size()=" << v.getsize() << endl;
	if (v.getsize() == 20) cout << "���Գɹ�" << endl;
	else cout << "����ʧ��" << endl;;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "����space()������" << endl;
	cout << "VECTOR�Ŀռ� v.space()=" << v.space() << endl;
	cout << "���гɹ�" << endl;
	cout << endl;
}
void t_insert() {
	VECTOR<int> v = get_int_data();
	cout << "ԭ���飺" << endl;;
	cout << v << endl;
	cout << endl;
	cout << "���±�5������6��666��" << endl;
	cout << "v.insert(666,5,6):" << endl;
	v.insert(666, 5, 6);
	cout << v << endl;
	cout << endl;
	cout << "���гɹ���" << endl;
}
void t_pushback_add() {
	VECTOR<int> t1 = get_int_data();
	VECTOR<int> t2 = get_int_data();
	VECTOR<int> t3 = get_int_data();
	VECTOR<int> t4 = get_int_data();
	cout << "��ȡ��������t1��t2,t3,t4��" << endl;
	cout << "ԭt1��" << t1 << endl;
	cout << "ԭt2��" << t2 << endl;
	cout << "ԭt3��" << t3 << endl;
	cout << "ԭt4��" << t4 << endl;
	cout << endl;
	cout << "����+=�������-------------------------------------------------------------------" << endl;
	t2 += t1;
	cout << "t2+=t1:"<<endl;
	cout<<"t2 = "<<t2 << endl;
	cout << "����+�������-------------------------------------------------------------------" << endl;
	t3 = t1 + t4;
	cout << "t3 = t1 + t4" << endl;
	cout<< "t3= "<< t3 << endl;
	cout << "����reverse������---------------------------------------------------------------" << endl;
	t3.reverse();
	cout << "t3.reverse()" << endl;
	cout<<"t3= " << t3 << endl;
	cout << "����push_back������-------------------------------------------------------------" << endl;
	t1.push_back(77);
	cout << "t1.push_back(77):" << endl;
	cout<<"ti= " << t1 << endl;
	cout << endl;
}
void menu()
{
	cout << "\n\n" << endl;
	cout << "===============   VECTOR������ģ��Ĳ���   ====================" << endl;
	cout << "===============================================================" << endl;
	cout << endl;
	cout << "  1 ---- ����earse���� ------------------------------------====\n" << endl;
	cout << "  2 ---- ���Ի�ȡ����ͷ��βԪ�غ��� -----------------------====\n" << endl;
	cout << "  3 ---- ���������������뵽�ı� -------------------------====\n" << endl;
	cout << "  4 ---- ���Ի�ȡ������С��ռ� ---------------------------====\n" << endl;
	cout << "  5 ---- ����insert()���� ---------------------------------====\n" << endl;
	cout << "  6 ---- ���ԡ�+������+=������reserve������push_back������ ====\n" << endl;
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
