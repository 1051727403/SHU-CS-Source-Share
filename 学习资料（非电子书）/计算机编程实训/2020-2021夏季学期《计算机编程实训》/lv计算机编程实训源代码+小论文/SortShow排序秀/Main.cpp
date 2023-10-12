// Main.cpp
#include "SortShow.h"
#include "SortA.h"
#include <stdlib.h>			// �� <cstdlib>
#include <time.h>			// �� <ctime>
#include <conio.h>

int main()
{
	char text[100];
	const char *str[]={	"1 ---- ��������ԭʼ����(D)",
						"2 ---- ð������........(B)",
						"3 ---- ѡ������........(S)",
						"4 ---- �鲢����........(M)",
						"5 ---- ��������........(Q)",
						"6 ---- �Ż���ѡ������..(P)",
						"7 ---- �Ż���ð������..(G)",
						"8 ---- �Ż��Ĺ鲢����..(N)",
						"0 ---- �˳�..........(ESC)",
						"��ѡ��: "};
	int choice, n = sizeof(str)/sizeof(*str);

	srand(time(NULL));

	Init();

	while(true)
	{
		SetConsoleTitle("SortShow������ - ������̿��ӻ�");
		system("cls");
		for(int i=0; i<n; i++)
			ShowText(20, i+2, 0, 7, str[i]);		// ��ʾ�˵�
		choice = getch();
		if(choice==27 || choice=='0')
			break;

		switch(choice)
		{
		case '1':
		case 'd':
		case 'D':	ShowText(2, 10, 0, 7, "1.����; 2.����; 3.���; 4.�ֹ����� 5.��Data.txt�ļ��ж�ȡ���� : ");
					SetData(getch()-'0');
					system("cls");
					ShowData();					break;
		case '2':
		case 'b':
		case 'B':	col1 = 30;
					SetConsoleTitle("ð������Bubble Sorting��");
					Start();
					Bubble_Sort(array, N);
					Finish();					break;
		case '3':
		case 's':
		case 'S':	col1 = 30;
					SetConsoleTitle("ѡ������Selection Sorting��");
					Start();
					Select_Sort(array, N);
					Finish();					break;
		case '4':
		case 'm':
		case 'M':	col1 = 5; col2 = col1 + 40;
					SetConsoleTitle("�鲢����Merge Sorting��");
					Start();
					Merge_Sort(array, N);
					Finish();					break;
		case '5':
		case 'q':
		case 'Q':	col1 = 40;
					SetConsoleTitle("��������Quick Sorting��");
					Start();
					Quick_Sort(array, N);
					Finish();					break;
		case '6':
		case 'p':
		case 'P':	col1 = 40;
					SetConsoleTitle("�Ż�ѡ������Selection_Primer Sorting��");
					Start();
					Select_Primer(array, N);
					Finish();					break;
		case '7':
		case 'G':
		case 'g':	col1 = 40;
					SetConsoleTitle("�Ż�ð������g_Primer Sorting��");
					Start();
					g_Bubble(array, N);
					Finish();					break;
		case '8':
		case 'N':
		case 'n':	col1 = 5;col2=col1+40;
					SetConsoleTitle("�Ż��鲢����Merge_Sort_Plus Sorting��");
					Start();
					Merge_Sort_Plus(array, N);
					Finish();					break;
					
		}
		sprintf(text, "���س�������...");
		ShowText(79-strlen(text), top+N+6, 0, 7, text);
		while(getch()!='\r') ;
	}
	Quit();
	return 0;
}
