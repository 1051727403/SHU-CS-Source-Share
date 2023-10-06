// Main.cpp
#include "LinkList.h"
#include "SongList.h"
#include <iomanip>
#include <string>
#include <cstring>
#include <conio.h>

int read()
{
	char temp;
	int r = 0;
	do { temp = getchar(); } while (temp < '0' || temp > '9');
	do { r = r * 10 + temp - '0'; temp = getchar(); } while (temp >= '0' && temp <= '9');
	if (temp != '\n') { char te[100]; cin.getline(te, 100); }
	return r;
}

int Pos(char ch, const char* str)			// ����ָ���ַ�ch���ַ���str�е��±ꡣ������ʱ����-1
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		if (ch == str[i])
			return i;
	return -1;
}

bool Check(LinkList<My_songlist>& user) {
	string Tname;
	cout << "ѡ��赥" << endl;
	cout << "��ѡ��id��ѯ���Ǹ赥����ѯ:0-id;1-name" << endl;
	bool f = 1;
	int op;
	op = read();
	if (op == 0) {
		cout << "������id: ";
		if (user.Go(read()) == NULL) cout << "δ��ѯ��" << endl, f = 0;
	}
	else {
		cout << "������赥��: ";
		cin >> Tname;
		if (user.Locate(string(Tname), 1) == NULL) cout << "δ��ѯ��" << endl, f = 0;
	}
	if (f) {
		cout << "�Ƿ�չʾ��ǰ�赥? 0��1��" << endl;
		cin >> op;
		if (op > 0)user.CurData().Showdel();
	}
	return f;
}

bool CheckSP(LinkList<My_songlist>& user) {
	string Tname;
	int num;
	cout << "--------ѡ��赥--------" << endl;
	cout << "ѡ��赥" << endl;
	cout << "��ѡ��id��ѯ���Ǹ赥����ѯ:0-id;1-name" << endl;
	bool f = 1;
	int op;
	op = read();
	if (op == 0) {
		cout << "������id: ";
		num = read();
		if (user.Go(num) == NULL) { cout << "δ��ѯ��" << endl, f = 0; }
	}
	else {
		cout << "������赥��: ";
		cin >> Tname;
		if (user.Locate(string(Tname), 1) == NULL) { cout << "δ��ѯ��" << endl, f = 0; }
	} 
	if (f) {
		user.CurData().Show(cout);
		cout << "============================================V1.0===" << endl;
		cout << "|��̖\t|" << "����\t\t\t|" << "��݋\t\t\t\t|" << "����\t\t\t|" << "�r�L\t|" << "��ʽ\t|" << "������\t|" << endl;
		user.CurData().Showdel();
	}
	return f;
}

void Addsonglist(LinkList<My_songlist>& user) {
	string Tname;
	cout << "�����赥" << endl;
	cout << "������赥���ƣ� " << endl;
	cin >> Tname;
	My_songlist xsonglist;
	xsonglist.Set_Title(Tname);
	cout << endl;
	cout << "(�ɰ�Enter����)�������飺 " << endl;
	getline(cin, Tname);
	getline(cin, Tname);
	if (Tname[0] != '\n')
		xsonglist.Set_Intro(Tname);
	user.Append(xsonglist);
	cout << "�����ɹ�" << endl;
}

void Addsong(LinkList<My_songlist>& user) {
	cout << "��������" << endl;
	user.CurData().Showdel();
	string Songname, Zhuanji, Writor, Type;
	double Len, Bit;
	cout << "���������: ";
	cin >> Songname;
	cout << "������ר����";
	cin >> Zhuanji;
	cout << "�����봴���ߣ�";
	cin >> Writor;
	cout << "�����볤�ȣ�";
	cin >> Len;
	cout << "�������ļ����ͣ�";
	cin >> Type;
	cout << "����������ʣ�";
	cin >> Bit;
	user.CurData().Addsong({ Songname,Zhuanji,Writor,Type,Len,Bit });
}

void AddsongO(LinkList<My_songlist>& user) {
	cout << "��������" << endl;
	Check(user);
	user.CurData().Showdel();
	string Songname, Zhuanji, Writor, Type;
	double Len, Bit;
	cout << "���������: ";
	cin >> Songname;
	cout << "������ר����";
	cin >> Zhuanji;
	cout << "�����봴���ߣ�";
	cin >> Writor;
	cout << "�����볤�ȣ�";
	cin >> Len;
	cout << "�������ļ����ͣ�";
	cin >> Type;
	cout << "����������ʣ�";
	cin >> Bit;
	user.CurData().Addsong({ Songname,Zhuanji,Writor,Type,Len,Bit });
}

void change_title(LinkList<My_songlist>& user) {
	string title;
	cout << "������赥����" << endl;
	cin >> title;
	user.CurData().Set_Title(title);
	cout << "���ĳɹ���" << endl;
}

void change_intro(LinkList<My_songlist>& user) {
	string intro;
	cout << "������赥��飺 " << endl;
	cin >> intro;
	user.CurData().Set_Intro(intro);
	cout << "���ĳɹ��� " << endl;
}

bool ShowSingle(LinkList<My_songlist>& user)
{
	cout << "��ѯ����" << endl;
	bool f = 1;
	if (user.NumNodes()) {
		cout << "��ѡ��id��ѯ���Ǹ�����ѯ:0 - id; 1 - name" << endl;
		string Tname;
		int op;
		op = read();
		if (op == 0) {
			cout << "������id: ";
			if (user.CurData().Go(read()) == NULL) { cout << "δ��ѯ��" << endl, f = 0; }
		}
		else {
			cout << "���������: ";
			cin >> Tname;
			if (user.CurData().Search(Tname) == NULL) { cout << "δ��ѯ��" << endl, f = 0; }
		}
		if (f) {
			user.CurData().ShowCur();
		}
	}
	return f;
}



bool Erase(LinkList<My_songlist>& user) {
	bool f = 1;
	int op = 0;
	if (user.CurNode() == NULL) {
		cout << "δ��ѯ��" << endl;
		f = 0;
	}
	if (f) {
		cout << "�Ƿ�չʾ��ǰ�赥? 0��1��" << endl;
		op = read();
		if (op == 1)user.CurData().Show(cout);
		cout << "�Ƿ�ɾ����0--��  1--��" << endl;
		op = read();
		if (op == 1)
		{
			user.DeleteCurNode();
		}
	}
	return f;
}

bool Erase_all(LinkList<My_songlist>& user) {

	bool f = 1;
	int op = 0;

	if (f) {
		cout << "�Ƿ�չʾ��ǰ�赥? 0��1��" << endl;
		op = read();
		if (op == 1)user.ShowList1();
		cout << "�Ƿ�ɾ����0--��  1--��" << endl;
		op = read();
		if (op == 1)
		{
			user.FreeList();
		}
	}
	return f;
}

bool Erase_song(LinkList<My_songlist>& user) {

	bool f = 1;
	int op = 0;

	if (f) {
		cout << "�Ƿ�չʾ��ǰ����? 0��1��" << endl;
		op = read();
		if (op == 1)user.CurData().ShowCur();
		cout << "�Ƿ�ɾ����0--��  1--��" << endl;
		op = read();
		if (op == 1)
		{
			user.CurData().delcurnode();
		}
	}
	return f;
}

void Modifysong(LinkList<My_songlist>& user) {
	if (user.CurData().song_nummm()) {
		cout << "�޸ĸ���" << endl;
			string Songname, Zhuanji, Writor, Type;
			double Len, Bit;
			cout << "�������¸���: ";
			cin >> Songname;
			cout << "��������ר����";
			cin >> Zhuanji;
			cout << "�������´����ߣ�";
			cin >> Writor;
			cout << "�������³��ȣ�";
			Len = read();
			cout << "���������ļ����ͣ�";
			cin >> Type;
			cout << "�������±����ʣ�";
			Bit = read();
			user.CurData().Set_Song({ Songname, Zhuanji, Writor, Type, Len, Bit });
	}
	else cout << "û�и���QAZ" << endl;
}

void LibraryTest()
{	
	/*
	cout << "�gӭ!" << endl;
	cout << "Ոݔ�������Ñ���: ";

	char filename[80] = "User";
	cin.getline(filename, 80);
	*/
	
	My_songlist list1("ROCK N ROLL", "Back to the 20th century, NIRVANA, OASIS, U2, LED ZEPPLIN, EAGLES~~~"),
		list2("���ĸ�����1", "�Ź��٣�����Ѹ��������ƽ��������������");

	LinkList<My_songlist> user;
	list1.ini1();
	list2.ini2();
	user.Append(list1);
	user.Append(list2);


	int key=0, key1=0, key2=0, key3=0;
	int Choice(const char* prompt, const char* options = "");	// Choice ��������
	while (true)
	{
		std::system("cls");
		cout << "\n\n================== Voiced Player ==================" << endl;
		cout << "  1 ---- ��  ��  ��  ��  (L)" << endl;
		cout << "  2 ---- ��  ԃ  ��  ��  (S)" << endl;
		cout << "  3 ---- ��  ԃ  ��  ��  (F)" << endl;
		cout << "  0 ---- ��  �Q  ��  ��(ESC)" << endl;
		cout << "============================================V1.0===" << endl;
		key = Choice("��ѡ��", "0123\x1blLsSfF");
		cout << "\n\n";
		if (key == 27 || key == '0')		// '\x1b'����27��ָESC��
			break;

		std::system("cls");
		switch (key)
		{
		case '1':
		case 'L':
		case 'l':
			std::system("cls");
			cout << "\n\n=================== �ҵĸ�� ===================" << endl;
			cout << "|\t��̖\t|\t\t" << setfill(' ') << setw(6) << "������Q" << "\t|" << endl;
			user.ShowList1();
			cout << endl << "===================================================" << endl;
			cout << "  1 ---- ��  �_  ��  ��  (O)" << endl;
			cout << "  2 ---- ��  ��  ��  ��  (A)" << endl;
			cout << "  3 ---- ��  ��      ��  (C)" << endl;
			cout << "  0 ---- ��          ��(ESC)" << endl;
			cout << "============================================V1.0===" << endl;
			key1 = Choice("��ѡ��", "0123\x1boOaACc");
			cout << "\n\n";
			if (key1 == 27 || key1 == '0')		// '\x1b'����27��ָESC��
				continue;

			switch (key1)
			{
			case '1':
			case 'O':
			case 'o':
				if (CheckSP(user)) {
					cout << "\n\n===================   ���   ===================" << endl;
					//cout << "|\t��̖\t|" << "\t����\t|" << "\t��݋\t|" << "\t����\t|" << "\t�r�L\t|" << "\t��ʽ\t|" << "\t������\t|" << endl;

					cout << "===================================================" << endl;
					cout << "  1 ---- ��  ��  ��  ��  (P)" << endl;
					cout << "  2 ---- ��  ��  ��  ��  (I)" << endl;
					cout << "  3 ---- ��  ��  ��  �Q  (N)" << endl;
					cout << "  4 ---- ��  ��  ��  ��  (A)" << endl;
					cout << "  5 ---- �h  ��  ��  ��  (D)" << endl;
					cout << "  0 ---- ��          ��(ESC)" << endl;
					cout << "============================================V1.0===" << endl;
					key2 = Choice("��ѡ��", "012345\x1bpPiInNaAdD");
					cout << "\n\n";
					if (key2 == 27 || key2 == '0')		// '\x1b'����27��ָESC��
						continue;
					switch (key2)
					{
					case '1':
					case 'P':
					case 'p':
						if (ShowSingle(user)) {
							cout << "===================================================" << endl;
							cout << "  1 ---- �h  ��  ��  ��  (S)" << endl;
							cout << "  2 ---- ��  ��  ��  ��  (M)" << endl;
							cout << "  0 ---- ��          ��(ESC)" << endl;
							cout << "============================================V1.0===" << endl;
							key3 = Choice("��ѡ��", "012\x1bsSmM");
							cout << "\n\n";
							if (key3 == 27 || key3 == '0')		// '\x1b'����27��ָESC��
								continue;
							std::system("cls");
							switch (key3)
							{
							case '1':
							case 'S':
							case 's':
								Erase_song(user);
								break;
							case '2':
							case 'M':
							case 'm':
								Modifysong(user);
								break;
							}
						}
						else cout << "---------���ĸ赥��û�и����ɹ�����QAQ--------" << endl;
						break;
					case '2':
					case 'I':
					case 'i':
						change_intro(user);
						break;
					case '3':
					case 'N':
					case 'n':
						change_title(user);
						break;
					case '4':
					case 'A':
					case 'a':
						Addsong(user);
						break;
					case '5':
					case 'D':
					case 'd':
						Erase(user);
						break;
					}
				}
				else cout << endl
					<< "--------��û�п��Դ򿪵ĸ赥QAQ---------" << endl;
				std::system("pause");
				break;
			case '2':
			case 'A':
			case 'a':
				Addsonglist(user);
				std::system("pause");
				break;
			case '3':
			case 'C':
			case 'c':
				Erase_all(user);
				break;
			}
			break;
		case '2':
		case 'S':
		case 's':
			Check(user);
			std::system("pause");
			break;
		case '3':
		case 'F':
		case 'f':
			ShowSingle(user);
			std::system("pause");
			break;
		}
		/*

		*/

	}
}



int Choice(const char* prompt, const char* options)		// �������塣�����ʾ��Ϣprompt������ѡ����ַ������ء�
{
	int key;
	cout << prompt << "{";
	for (int i = 0; options[i] != '\0'; i++)
	{
		if (' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// ѡ��options�еĿɴ�ӡ�ַ�
			cout << options[i] << ' ';
		else														// ѡ��options�еĲ��ֿ����ַ�
		{
			switch (options[i])
			{
			case '\t':   cout << "[Tab] ";   break;					// ѡ���е�Tab�ַ�'\t'����ASCII����9��
			case '\x1b': cout << "[Esc] ";   break;					// ѡ���е�Esc�ַ�'\x1b'����ASCII����27��
			case ' ':    cout << "[Space] "; break;					// ѡ���еĿո��ַ�' '����ASCII����32��
			}
		}
	}
	cout << "\b}: ";					// '\b'�˸�����һ��������һ�����
	do
	{
		key = getch();
	} while (options[0] != '\0' && Pos(key, options) < 0); // ��optionsΪ�ճ���Ϊ0���ַ����������������ƣ�����������Ӧ����optins�С�
	cout << endl;
	return key;
}

int main()
{



	LibraryTest();
	return 0;
}