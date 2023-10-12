// SortShow.cpp
#include "SortShow.h"
#include <stdlib.h>			// �� <cstdlib>
#include <time.h>			// �� <ctime>
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

// ��Ȼʹ��ȫ�ֱ����ᵼ�¿���ֲ�Ա���Ϊ�˼��ٺ������βΣ��ؽ����������Ƴ�ȫ�ֱ���
// �˴�Ϊ����������Ķ���
HANDLE			hStdIn, hStdOut;						// ��׼����/����ľ��
HMIDIOUT		hMidiOut;								// MIDI����豸���
unsigned char	notes[8] = {48, 50, 52, 53, 55, 57, 59};// С����do,re,mi,fa,sol,la,si
int				array0[N], array[N], temp[N];
int				col1 = 5, col2 = 45, top = 1, r = 2;	// ������ʾ����ʼ�С���

DWORD MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume)//Ϊ�������midiOutShortMsg����
{//����Charles Petzold��Windows�������(��ذ�)����5��[��������],�廪��ѧ������,2010��. ��22.3.5С���еĴ���(��1042ҳ)
	DWORD dwMessage = (iVolume << 16) | (iNote << 8) | iStatus         | iChannel;
					//      ����      |     ����     | ״̬�ֽ�(��4λ) | ͨ��(��4λ)
	return midiOutShortMsg(hMidiOut, dwMessage);
}

void Init()												// ��ʼ����
{	
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);			// ��ȡ��׼������
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);			// ��ȡ��׼������
	DWORD fdwMode;
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	fdwMode &= ~ENABLE_QUICK_EDIT_MODE;	// �ǳ��ؼ���һ�㣺�رտ���̨�����е�"���ٱ༭ģʽ"���ܲ���������¼�
	fdwMode &= ~ENABLE_INSERT_MODE;
	SetConsoleMode(hStdIn, fdwMode);
	SetConsoleTitle("SortShow������ - ������̿��ӻ�");	// ���ô��ڱ���
	midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);		// ��MIDI����ӳ���豸
	SetData(3);											// ����ԭʼ���ݣ������
}

void Quit()
{
	midiOutClose(hMidiOut);		// �ر�MIDI����豸
	CloseHandle(hStdOut);
	CloseHandle(hStdIn);
}

void ShowChar(int x, int y, int bkcolor, int color, char ch)
{
	char str[2] = {ch, '\0'};
	ShowText(x, y, bkcolor, color, str);
}

void ShowText(int x, int y, int bkcolor, int color, const char *str)
{
	DWORD result;
	COORD coord = {x, y};
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, bkcolor<<4 | color);
	WriteConsole(hStdOut, str, strlen(str), &result, NULL);
}

void Read(const char *filename)
{
	int i=0;
	char str[80];
	ifstream infile(filename);
	if(infile.fail() || filename[0]=='\0')
	{
		sprintf(str, "������ %d ��1~%d֮���������", N, N);
		ShowText(2, 12, 0, 7, str);
		for(int j=0; j<N; j++)
			cin >> array0[j];
	}
	else
	{
		for(; i<N && infile>>array0[i]; i++)
			;
		for( ; i<N; i++)
			array0[i] = rand() % N + 1;
		infile.close();
	}
}

void SetData(int flag)
{
	int i;
	switch(flag)
	{
	case 1: for(i=0; i<N; i++) array0[i] = i+1;				break;
	case 2: for(i=0; i<N; i++) array0[i] = N-i;				break;
	case 4: Read("");										break;
	case 5:	Read("Data.txt");								break;
	default:for(i=0; i<N; i++) array0[i] = i+1;
			for(int k=N*N/2; k>0; k--)
				swap(array0[rand()%N], array0[rand()%N]);
															break;
	}
	for(int i=0; i<N; i++)
		array[i] = array0[i];
}

void ReSetData()			// �ָ����ݣ�������array0�е����ݵ��뵽����array�У�
{
	for(int i=0; i < N; i++)
		array[i] = array0[i];
}

void ShowData()
{
	for(int i=0; i<N; i++)
		ShowBar(col1, i+top, array[i]);
}

void Start()											// ����׼����ʼ
{
	ReSetData();										// �ָ����ݣ�ʹ����ͬ������׼������
	SetConsoleTextAttribute(hStdOut, 7);				// �ڵװ���
	system("cls");										// ����
	ShowData();											// ԭʼ����
	
	ShowText(3, top+N+2, 4, 14, "���������1���ӿ�ʼ...");	// ����:��(4), ǰ��:��(14)
	getch();
	MidiOutMessage(hMidiOut, 0x90, 0x09, 71, 127);		// ͨ��0x09��ָ����֣�71Ϊ Short Whistle ���ڣ�
	ShowText(3, top+N+2, 4, 14, "���������......      ");	// ����:��(4), ǰ��:��(14)
	Sleep(1000);
}

void Finish()											// �������
{
	MidiOutMessage(hMidiOut, 0x90, 0x09, 46, 127);		// ͨ��0x09��ָ����֣�46Ϊ Open Hi-Hat �������
	Sleep(200);
	ShowData();
	ShowText(3, top+N+2, 14, 4, "������ɣ�������... ");	// ����:��(14), ǰ��:��(4)
	ShowText(0, top+N+3, 0, 7, "");
}

void ShowBar(int x, int y, int value, bool blinding)
{
	char bar[41];
	DWORD result;
	COORD coord = {x, y};
	int color = (value==15? 15 : value % 15);
	int note = notes[(value-1)%7] + 12*((value-1)/7);

	sprintf(bar, "%2d%38s", value, "");
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*Ϊ������������note�����������:127
	while(true)
	{
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, 7);			// �����ڡ�ǰ����
		WriteConsole(hStdOut, bar, r*value, &result, NULL);
		Sleep(50);
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, color<<4 | 15-color);	// ����ɫ��ǰ��ɫ
		WriteConsole(hStdOut, bar, r*value, &result, NULL);
		Sleep(50);
		if(!blinding)
			break;
		if(kbhit())
		{
			getch();
			break;
		}
	}
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127
}

void ShowBars(int x1, int y1, int value1, int x2, int y2, int value2, bool blinding)
{
	char bar1[41], bar2[41];
	DWORD result;
	COORD coord1 = {x1, y1}, coord2 = {x2, y2};
	int color1 = (value1==15? 15 : value1 % 15);
	int color2 = (value2==15? 15 : value2 % 15);
	int note1 = notes[(value1-1)%7] + 12*((value1-1)/7);
	int note2 = notes[(value2-1)%7] + 12*((value2-1)/7);

	sprintf(bar1, "%2d%38s", value1, "");
	sprintf(bar2, "%2d%38s", value2, "");
	while(true)
	{
		MidiOutMessage(hMidiOut, 0x90, 0, note1, 127);		// 0x9*Ϊ������������note�����������:127
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, 7);				// �����ڡ�ǰ����
		WriteConsole(hStdOut, bar1, r*value1, &result, NULL);
		Sleep(100);
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, color1<<4 | 15-color1);	// ����ɫ��ǰ��ɫ
		WriteConsole(hStdOut, bar1, r*value1, &result, NULL);
		Sleep(100);
		MidiOutMessage(hMidiOut, 0x80, 0, note1, 127);		// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127

		MidiOutMessage(hMidiOut, 0x90, 0, note2, 127);		// 0x9*Ϊ������������note�����������:127
		SetConsoleCursorPosition(hStdOut, coord2);
		SetConsoleTextAttribute(hStdOut, 7);				// �����ڡ�ǰ����
		WriteConsole(hStdOut, bar2, r*value2, &result, NULL);
		Sleep(100);
		SetConsoleCursorPosition(hStdOut, coord2);
		SetConsoleTextAttribute(hStdOut, color2<<4 | 15-color2);	// ����ɫ��ǰ��ɫ
		WriteConsole(hStdOut, bar2, r*value2, &result, NULL);
		Sleep(100);
		MidiOutMessage(hMidiOut, 0x80, 0, note2, 127);		// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127
		if(!blinding)
			break;
		if(kbhit())
		{
			getch();
			break;
		}
	}
}

void MoveBar(int x0, int y0, int len, int x1, int y1)
{
	DWORD result, num;
	COORD coord = {x0, y0};
	WORD attr[40];
	char str[40], spaces[40];
	int note = notes[(len/r-1)%7] + 12*((len/r-1)/7);

	MidiOutMessage(hMidiOut, 0x90, 0x09, 84, 127);		// ͨ��0x09��ָ����֣�84ΪBell Tree������
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*Ϊ������������note�����������:127
	Sleep(100);
	sprintf(spaces, "%40s", "");
	ReadConsoleOutputCharacter(hStdOut, str, len, coord, &num);
	ReadConsoleOutputAttribute(hStdOut, attr, len, coord, &num);

	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 0);				// ��ɫ
	WriteConsole(hStdOut, spaces, len, &result, NULL);

	coord.X = x1;
	coord.Y = y1;
	for(int i=0; i<len; i++,coord.X++)
	{
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, attr[i]);
		WriteConsole(hStdOut, str+i, 1, &result, NULL);
	}
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127
}

void SWAP(int *a, int i, int j)			// �˴���x��һ����array
{
	int i1 = a - array + i;
	int j1 = a - array + j;
	if(i1<0 || j1<0 || i1>=N || j1>=N)
		return ;

	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// ͨ��0x09��ָ����֣�38ΪAcoustic Snare (С��)
	ShowBars(col1, top+i1, array[i1], col1, top+j1, array[j1], true);

	DWORD result;
	COORD coord={col1, top+i1};
	char str[41];
	int len = r*array[i1];
	sprintf(str, "%40s", "");
	if(array[i1] < array[j1])							// Ϊ��"Ĩȥ"����������β����ɫ
	{
		coord.Y = top+j1;
		len = r*array[j1];
	}
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 0);
	WriteConsole(hStdOut, str, r*len, &result, NULL);

	int temp = array[i1];
	array[i1] = array[j1];
	array[j1] = temp;
	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// ͨ��0x09��ָ����֣�38ΪAcoustic Snare (С��)
	ShowBars(col1, top+i1, array[i1], col1, top+j1, array[j1]);	// �����󣨲���ͣ��
}

void ShowAfterSwap( int *arr,int *temparr,int size,bool blinding)
{
	char bar[41];
	DWORD result;
	int color[size];
	MidiOutMessage(hMidiOut, 0x90, 0, 48, 127);		// 0x9*Ϊ������������note�����������:127
	while(true)
	{
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", arr[i], "");
			COORD coord = {col1, top+i};
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, 7);			// �����ڡ�ǰ����
			WriteConsole(hStdOut, bar, r*arr[i], &result, NULL);
		}
		Sleep(100);
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", arr[i], "");
			COORD coord = {col1, top+i};
			color[i] = (arr[i]==15? 15 : arr[i] % 15);
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, color[i]<<4 | 15-color[i]);	// ����ɫ��ǰ��ɫ
			WriteConsole(hStdOut, bar, r*arr[i], &result, NULL);
			
		}
		Sleep(100);
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", temparr[i], "");
			COORD coord = {col2, top+i};
			color[i] = (temparr[i]==15? 15 : temparr[i] % 15);
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, 7);			// �����ڡ�ǰ����
			WriteConsole(hStdOut, bar, r*temparr[i], &result, NULL);
		}
		Sleep(100);
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", temparr[i], "");
			COORD coord = {col2, top+i};
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, color[i]<<4 | 15-color[i]);	// ����ɫ��ǰ��ɫ
			WriteConsole(hStdOut, bar, r*temparr[i], &result, NULL);
		}
		Sleep(100);
		if(!blinding)
			break;
		if(kbhit())
		{
			getch(); break;
		}
	}
	MidiOutMessage(hMidiOut, 0x80, 0, 48, 127);		// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127
}
void SwapTotal(int *arr, int *temparr,int size)			// �˴���x��һ����array
{
	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// ͨ��0x09��ָ����֣�38ΪAcoustic Snare (С��)
	ShowAfterSwap(arr,temparr,size,true);
	DWORD result;
	for(int i=0;i<size;i++){
		COORD coord={col1, top+i};
		char str[41];
		int len = r*arr[i];
		sprintf(str, "%40s", "");
		if(arr[i] < temparr[i])							// Ϊ��"Ĩȥ"����������β����ɫ
		{
			coord.X = col2;
			len = r*temparr[i];
		}
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, 0);
		WriteConsole(hStdOut, str, r*len, &result, NULL);
		int temp = arr[i];
		array[i] = temparr[i];
		temparr[i] = temp;
	}
	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// ͨ��0x09��ָ����֣�38ΪAcoustic Snare (С��)
	ShowAfterSwap(arr,temparr,size,false);	// �����󣨲���ͣ��
}
void MoveAway(int x0, int y0, int lenarr)
{
	DWORD result;
	char spaces[40];
	int note = notes[(lenarr/r-1)%7] + 12*((lenarr/r-1)/7);
	MidiOutMessage(hMidiOut, 0x90, 0x09, 84, 127);		// ͨ��0x09��ָ����֣�84ΪBell Tree������
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*Ϊ������������note�����������:127
	Sleep(100);
	COORD coord = {x0, y0};
	sprintf(spaces, "%40s", "");
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 0);				// ��ɫ
	WriteConsole(hStdOut, spaces, lenarr, &result, NULL);
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127
}
void MoveIn(int x0, int y0, int lentemparr)
{
	DWORD result;
	char str[40];
	int note = notes[(lentemparr/r-1)%7] + 12*((lentemparr/r-1)/7);
	COORD coord = {x0, y0};
	MidiOutMessage(hMidiOut, 0x90, 0x09, 84, 127);		// ͨ��0x09��ָ����֣�84ΪBell Tree������
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*Ϊ������������note�����������:127
	Sleep(100);
	sprintf(str, "%2d%38s", lentemparr/2, "");
	//ReadConsoleOutputCharacter(hStdOut, str, lentemparr/2, coord, &num);
	int color = ((lentemparr/2)==15? 15 : (lentemparr/2) % 15);
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut,  color<<4 | 15-color);
	WriteConsole(hStdOut, str, lentemparr, &result, NULL);
	getch();
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127
}
