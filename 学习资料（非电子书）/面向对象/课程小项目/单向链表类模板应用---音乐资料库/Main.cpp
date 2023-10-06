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

int Pos(char ch, const char* str)			// 返回指定字符ch在字符串str中的下标。不存在时返回-1
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		if (ch == str[i])
			return i;
	return -1;
}

bool Check(LinkList<My_songlist>& user) {
	string Tname;
	cout << "选择歌单" << endl;
	cout << "请选择id查询还是歌单名查询:0-id;1-name" << endl;
	bool f = 1;
	int op;
	op = read();
	if (op == 0) {
		cout << "请输入id: ";
		if (user.Go(read()) == NULL) cout << "未查询到" << endl, f = 0;
	}
	else {
		cout << "请输入歌单名: ";
		cin >> Tname;
		if (user.Locate(string(Tname), 1) == NULL) cout << "未查询到" << endl, f = 0;
	}
	if (f) {
		cout << "是否展示当前歌单? 0否：1是" << endl;
		cin >> op;
		if (op > 0)user.CurData().Showdel();
	}
	return f;
}

bool CheckSP(LinkList<My_songlist>& user) {
	string Tname;
	int num;
	cout << "--------选择歌单--------" << endl;
	cout << "选择歌单" << endl;
	cout << "请选择id查询还是歌单名查询:0-id;1-name" << endl;
	bool f = 1;
	int op;
	op = read();
	if (op == 0) {
		cout << "请输入id: ";
		num = read();
		if (user.Go(num) == NULL) { cout << "未查询到" << endl, f = 0; }
	}
	else {
		cout << "请输入歌单名: ";
		cin >> Tname;
		if (user.Locate(string(Tname), 1) == NULL) { cout << "未查询到" << endl, f = 0; }
	} 
	if (f) {
		user.CurData().Show(cout);
		cout << "============================================V1.0===" << endl;
		cout << "|序號\t|" << "歌名\t\t\t|" << "專輯\t\t\t\t|" << "作者\t\t\t|" << "時長\t|" << "格式\t|" << "比特率\t|" << endl;
		user.CurData().Showdel();
	}
	return f;
}

void Addsonglist(LinkList<My_songlist>& user) {
	string Tname;
	cout << "新增歌单" << endl;
	cout << "请输入歌单名称： " << endl;
	cin >> Tname;
	My_songlist xsonglist;
	xsonglist.Set_Title(Tname);
	cout << endl;
	cout << "(可按Enter跳过)请输入简介： " << endl;
	getline(cin, Tname);
	getline(cin, Tname);
	if (Tname[0] != '\n')
		xsonglist.Set_Intro(Tname);
	user.Append(xsonglist);
	cout << "新增成功" << endl;
}

void Addsong(LinkList<My_songlist>& user) {
	cout << "新增歌曲" << endl;
	user.CurData().Showdel();
	string Songname, Zhuanji, Writor, Type;
	double Len, Bit;
	cout << "请输入歌名: ";
	cin >> Songname;
	cout << "请输入专辑：";
	cin >> Zhuanji;
	cout << "请输入创作者：";
	cin >> Writor;
	cout << "请输入长度：";
	cin >> Len;
	cout << "请输入文件类型：";
	cin >> Type;
	cout << "请输入比特率：";
	cin >> Bit;
	user.CurData().Addsong({ Songname,Zhuanji,Writor,Type,Len,Bit });
}

void AddsongO(LinkList<My_songlist>& user) {
	cout << "新增歌曲" << endl;
	Check(user);
	user.CurData().Showdel();
	string Songname, Zhuanji, Writor, Type;
	double Len, Bit;
	cout << "请输入歌名: ";
	cin >> Songname;
	cout << "请输入专辑：";
	cin >> Zhuanji;
	cout << "请输入创作者：";
	cin >> Writor;
	cout << "请输入长度：";
	cin >> Len;
	cout << "请输入文件类型：";
	cin >> Type;
	cout << "请输入比特率：";
	cin >> Bit;
	user.CurData().Addsong({ Songname,Zhuanji,Writor,Type,Len,Bit });
}

void change_title(LinkList<My_songlist>& user) {
	string title;
	cout << "请输入歌单名：" << endl;
	cin >> title;
	user.CurData().Set_Title(title);
	cout << "更改成功！" << endl;
}

void change_intro(LinkList<My_songlist>& user) {
	string intro;
	cout << "请输入歌单简介： " << endl;
	cin >> intro;
	user.CurData().Set_Intro(intro);
	cout << "更改成功！ " << endl;
}

bool ShowSingle(LinkList<My_songlist>& user)
{
	cout << "查询歌曲" << endl;
	bool f = 1;
	if (user.NumNodes()) {
		cout << "请选择id查询还是歌名查询:0 - id; 1 - name" << endl;
		string Tname;
		int op;
		op = read();
		if (op == 0) {
			cout << "请输入id: ";
			if (user.CurData().Go(read()) == NULL) { cout << "未查询到" << endl, f = 0; }
		}
		else {
			cout << "请输入歌名: ";
			cin >> Tname;
			if (user.CurData().Search(Tname) == NULL) { cout << "未查询到" << endl, f = 0; }
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
		cout << "未查询到" << endl;
		f = 0;
	}
	if (f) {
		cout << "是否展示当前歌单? 0否：1是" << endl;
		op = read();
		if (op == 1)user.CurData().Show(cout);
		cout << "是否删除？0--否  1--是" << endl;
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
		cout << "是否展示当前歌单? 0否：1是" << endl;
		op = read();
		if (op == 1)user.ShowList1();
		cout << "是否删除？0--否  1--是" << endl;
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
		cout << "是否展示当前歌曲? 0否：1是" << endl;
		op = read();
		if (op == 1)user.CurData().ShowCur();
		cout << "是否删除？0--否  1--是" << endl;
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
		cout << "修改歌曲" << endl;
			string Songname, Zhuanji, Writor, Type;
			double Len, Bit;
			cout << "请输入新歌名: ";
			cin >> Songname;
			cout << "请输入新专辑：";
			cin >> Zhuanji;
			cout << "请输入新创作者：";
			cin >> Writor;
			cout << "请输入新长度：";
			Len = read();
			cout << "请输入新文件类型：";
			cin >> Type;
			cout << "请输入新比特率：";
			Bit = read();
			user.CurData().Set_Song({ Songname, Zhuanji, Writor, Type, Len, Bit });
	}
	else cout << "没有歌曲QAZ" << endl;
}

void LibraryTest()
{	
	/*
	cout << "歡迎!" << endl;
	cout << "請輸入您的用戶名: ";

	char filename[80] = "User";
	cin.getline(filename, 80);
	*/
	
	My_songlist list1("ROCK N ROLL", "Back to the 20th century, NIRVANA, OASIS, U2, LED ZEPPLIN, EAGLES~~~"),
		list2("中文歌曲集1", "张国荣，陈奕迅，朴树，平凡的我们与他们");

	LinkList<My_songlist> user;
	list1.ini1();
	list2.ini2();
	user.Append(list1);
	user.Append(list2);


	int key=0, key1=0, key2=0, key3=0;
	int Choice(const char* prompt, const char* options = "");	// Choice 函數申明
	while (true)
	{
		std::system("cls");
		cout << "\n\n================== Voiced Player ==================" << endl;
		cout << "  1 ---- 我  的  歌  單  (L)" << endl;
		cout << "  2 ---- 查  詢  歌  單  (S)" << endl;
		cout << "  3 ---- 查  詢  歌  曲  (F)" << endl;
		cout << "  0 ---- 切  換  用  戶(ESC)" << endl;
		cout << "============================================V1.0===" << endl;
		key = Choice("请选择", "0123\x1blLsSfF");
		cout << "\n\n";
		if (key == 27 || key == '0')		// '\x1b'等于27，指ESC键
			break;

		std::system("cls");
		switch (key)
		{
		case '1':
		case 'L':
		case 'l':
			std::system("cls");
			cout << "\n\n=================== 我的歌單 ===================" << endl;
			cout << "|\t序號\t|\t\t" << setfill(' ') << setw(6) << "歌單名稱" << "\t|" << endl;
			user.ShowList1();
			cout << endl << "===================================================" << endl;
			cout << "  1 ---- 打  開  歌  單  (O)" << endl;
			cout << "  2 ---- 新  增  歌  單  (A)" << endl;
			cout << "  3 ---- 清  空      库  (C)" << endl;
			cout << "  0 ---- 返          回(ESC)" << endl;
			cout << "============================================V1.0===" << endl;
			key1 = Choice("请选择", "0123\x1boOaACc");
			cout << "\n\n";
			if (key1 == 27 || key1 == '0')		// '\x1b'等于27，指ESC键
				continue;

			switch (key1)
			{
			case '1':
			case 'O':
			case 'o':
				if (CheckSP(user)) {
					cout << "\n\n===================   歌單   ===================" << endl;
					//cout << "|\t序號\t|" << "\t歌名\t|" << "\t專輯\t|" << "\t作者\t|" << "\t時長\t|" << "\t格式\t|" << "\t比特率\t|" << endl;

					cout << "===================================================" << endl;
					cout << "  1 ---- 播  放  歌  曲  (P)" << endl;
					cout << "  2 ---- 修  改  簡  介  (I)" << endl;
					cout << "  3 ---- 修  改  名  稱  (N)" << endl;
					cout << "  4 ---- 新  增  歌  曲  (A)" << endl;
					cout << "  5 ---- 刪  除  歌  單  (D)" << endl;
					cout << "  0 ---- 返          回(ESC)" << endl;
					cout << "============================================V1.0===" << endl;
					key2 = Choice("请选择", "012345\x1bpPiInNaAdD");
					cout << "\n\n";
					if (key2 == 27 || key2 == '0')		// '\x1b'等于27，指ESC键
						continue;
					switch (key2)
					{
					case '1':
					case 'P':
					case 'p':
						if (ShowSingle(user)) {
							cout << "===================================================" << endl;
							cout << "  1 ---- 刪  除  歌  曲  (S)" << endl;
							cout << "  2 ---- 修  改  歌  曲  (M)" << endl;
							cout << "  0 ---- 返          回(ESC)" << endl;
							cout << "============================================V1.0===" << endl;
							key3 = Choice("请选择", "012\x1bsSmM");
							cout << "\n\n";
							if (key3 == 27 || key3 == '0')		// '\x1b'等于27，指ESC键
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
						else cout << "---------您的歌单中没有歌曲可供更改QAQ--------" << endl;
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
					<< "--------您没有可以打开的歌单QAQ---------" << endl;
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



int Choice(const char* prompt, const char* options)		// 函数定义。输出提示信息prompt，输入选择的字符并返回。
{
	int key;
	cout << prompt << "{";
	for (int i = 0; options[i] != '\0'; i++)
	{
		if (' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// 选项options中的可打印字符
			cout << options[i] << ' ';
		else														// 选项options中的部分控制字符
		{
			switch (options[i])
			{
			case '\t':   cout << "[Tab] ";   break;					// 选项中的Tab字符'\t'（即ASCII编码9）
			case '\x1b': cout << "[Esc] ";   break;					// 选项中的Esc字符'\x1b'（即ASCII编码27）
			case ' ':    cout << "[Space] "; break;					// 选项中的空格字符' '（即ASCII编码32）
			}
		}
	}
	cout << "\b}: ";					// '\b'退格。先退一格，在输出右花括号
	do
	{
		key = getch();
	} while (options[0] != '\0' && Pos(key, options) < 0); // 若options为空长度为0的字符串，则输入无限制；否则输入项应该在optins中。
	cout << endl;
	return key;
}

int main()
{



	LibraryTest();
	return 0;
}