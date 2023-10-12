// SortShow.cpp
#include "SortShow.h"
#include <stdlib.h>			// 或 <cstdlib>
#include <time.h>			// 或 <ctime>
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

// 虽然使用全局变量会导致可移植性变差，但为了减少函数的形参，特将下面变量设计成全局变量
// 此处为变量及数组的定义
HANDLE			hStdIn, hStdOut;						// 标准输入/输出的句柄
HMIDIOUT		hMidiOut;								// MIDI输出设备句柄
unsigned char	notes[8] = {48, 50, 52, 53, 55, 57, 59};// 小字组do,re,mi,fa,sol,la,si
int				array0[N], array[N], temp[N];
int				col1 = 5, col2 = 45, top = 1, r = 2;	// 数据显示的起始列、行

DWORD MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume)//为方便调用midiOutShortMsg函数
{//引自Charles Petzold《Windows程序设计(珍藏版)》第5版[方敏等译],清华大学出版社,2010年. 第22.3.5小节中的代码(第1042页)
	DWORD dwMessage = (iVolume << 16) | (iNote << 8) | iStatus         | iChannel;
					//      音量      |     音符     | 状态字节(高4位) | 通道(低4位)
	return midiOutShortMsg(hMidiOut, dwMessage);
}

void Init()												// 初始设置
{	
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);			// 获取标准输入句柄
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);			// 获取标准输出句柄
	DWORD fdwMode;
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	fdwMode &= ~ENABLE_QUICK_EDIT_MODE;	// 非常关键的一点：关闭控制台属性中的"快速编辑模式"才能不阻塞鼠标事件
	fdwMode &= ~ENABLE_INSERT_MODE;
	SetConsoleMode(hStdIn, fdwMode);
	SetConsoleTitle("SortShow排序秀 - 排序过程可视化");	// 设置窗口标题
	midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);		// 打开MIDI播放映射设备
	SetData(3);											// 设置原始数据（随机序）
}

void Quit()
{
	midiOutClose(hMidiOut);		// 关闭MIDI输出设备
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
		sprintf(str, "请输入 %d 个1~%d之间的整数：", N, N);
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

void ReSetData()			// 恢复数据（将数组array0中的数据导入到数组array中）
{
	for(int i=0; i < N; i++)
		array[i] = array0[i];
}

void ShowData()
{
	for(int i=0; i<N; i++)
		ShowBar(col1, i+top, array[i]);
}

void Start()											// 排序准备开始
{
	ReSetData();										// 恢复数据（使用相同的数据准备排序）
	SetConsoleTextAttribute(hStdOut, 7);				// 黑底白字
	system("cls");										// 清屏
	ShowData();											// 原始数据
	
	ShowText(3, top+N+2, 4, 14, "按任意键后1秒钟开始...");	// 背景:红(4), 前景:黄(14)
	getch();
	MidiOutMessage(hMidiOut, 0x90, 0x09, 71, 127);		// 通道0x09特指打击乐（71为 Short Whistle 短哨）
	ShowText(3, top+N+2, 4, 14, "排序进行中......      ");	// 背景:红(4), 前景:黄(14)
	Sleep(1000);
}

void Finish()											// 排序结束
{
	MidiOutMessage(hMidiOut, 0x90, 0x09, 46, 127);		// 通道0x09特指打击乐（46为 Open Hi-Hat 开音踩镲）
	Sleep(200);
	ShowData();
	ShowText(3, top+N+2, 14, 4, "排序完成，输出结果... ");	// 背景:黄(14), 前景:红(4)
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
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*为开音（即播放note），音量最大:127
	while(true)
	{
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, 7);			// 背景黑、前景白
		WriteConsole(hStdOut, bar, r*value, &result, NULL);
		Sleep(50);
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, color<<4 | 15-color);	// 背景色、前景色
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
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127
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
		MidiOutMessage(hMidiOut, 0x90, 0, note1, 127);		// 0x9*为开音（即播放note），音量最大:127
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, 7);				// 背景黑、前景白
		WriteConsole(hStdOut, bar1, r*value1, &result, NULL);
		Sleep(100);
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, color1<<4 | 15-color1);	// 背景色、前景色
		WriteConsole(hStdOut, bar1, r*value1, &result, NULL);
		Sleep(100);
		MidiOutMessage(hMidiOut, 0x80, 0, note1, 127);		// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127

		MidiOutMessage(hMidiOut, 0x90, 0, note2, 127);		// 0x9*为开音（即播放note），音量最大:127
		SetConsoleCursorPosition(hStdOut, coord2);
		SetConsoleTextAttribute(hStdOut, 7);				// 背景黑、前景白
		WriteConsole(hStdOut, bar2, r*value2, &result, NULL);
		Sleep(100);
		SetConsoleCursorPosition(hStdOut, coord2);
		SetConsoleTextAttribute(hStdOut, color2<<4 | 15-color2);	// 背景色、前景色
		WriteConsole(hStdOut, bar2, r*value2, &result, NULL);
		Sleep(100);
		MidiOutMessage(hMidiOut, 0x80, 0, note2, 127);		// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127
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

	MidiOutMessage(hMidiOut, 0x90, 0x09, 84, 127);		// 通道0x09特指打击乐（84为Bell Tree铃树）
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*为开音（即播放note），音量最大:127
	Sleep(100);
	sprintf(spaces, "%40s", "");
	ReadConsoleOutputCharacter(hStdOut, str, len, coord, &num);
	ReadConsoleOutputAttribute(hStdOut, attr, len, coord, &num);

	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 0);				// 黑色
	WriteConsole(hStdOut, spaces, len, &result, NULL);

	coord.X = x1;
	coord.Y = y1;
	for(int i=0; i<len; i++,coord.X++)
	{
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, attr[i]);
		WriteConsole(hStdOut, str+i, 1, &result, NULL);
	}
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127
}

void SWAP(int *a, int i, int j)			// 此处的x不一定是array
{
	int i1 = a - array + i;
	int j1 = a - array + j;
	if(i1<0 || j1<0 || i1>=N || j1>=N)
		return ;

	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// 通道0x09特指打击乐，38为Acoustic Snare (小鼓)
	ShowBars(col1, top+i1, array[i1], col1, top+j1, array[j1], true);

	DWORD result;
	COORD coord={col1, top+i1};
	char str[41];
	int len = r*array[i1];
	sprintf(str, "%40s", "");
	if(array[i1] < array[j1])							// 为了"抹去"更长的条的尾部颜色
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
	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// 通道0x09特指打击乐，38为Acoustic Snare (小鼓)
	ShowBars(col1, top+i1, array[i1], col1, top+j1, array[j1]);	// 交换后（不暂停）
}

void ShowAfterSwap( int *arr,int *temparr,int size,bool blinding)
{
	char bar[41];
	DWORD result;
	int color[size];
	MidiOutMessage(hMidiOut, 0x90, 0, 48, 127);		// 0x9*为开音（即播放note），音量最大:127
	while(true)
	{
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", arr[i], "");
			COORD coord = {col1, top+i};
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, 7);			// 背景黑、前景白
			WriteConsole(hStdOut, bar, r*arr[i], &result, NULL);
		}
		Sleep(100);
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", arr[i], "");
			COORD coord = {col1, top+i};
			color[i] = (arr[i]==15? 15 : arr[i] % 15);
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, color[i]<<4 | 15-color[i]);	// 背景色、前景色
			WriteConsole(hStdOut, bar, r*arr[i], &result, NULL);
			
		}
		Sleep(100);
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", temparr[i], "");
			COORD coord = {col2, top+i};
			color[i] = (temparr[i]==15? 15 : temparr[i] % 15);
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, 7);			// 背景黑、前景白
			WriteConsole(hStdOut, bar, r*temparr[i], &result, NULL);
		}
		Sleep(100);
		for(int i=0;i<size;i++){
			sprintf(bar, "%2d%38s", temparr[i], "");
			COORD coord = {col2, top+i};
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, color[i]<<4 | 15-color[i]);	// 背景色、前景色
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
	MidiOutMessage(hMidiOut, 0x80, 0, 48, 127);		// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127
}
void SwapTotal(int *arr, int *temparr,int size)			// 此处的x不一定是array
{
	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// 通道0x09特指打击乐，38为Acoustic Snare (小鼓)
	ShowAfterSwap(arr,temparr,size,true);
	DWORD result;
	for(int i=0;i<size;i++){
		COORD coord={col1, top+i};
		char str[41];
		int len = r*arr[i];
		sprintf(str, "%40s", "");
		if(arr[i] < temparr[i])							// 为了"抹去"更长的条的尾部颜色
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
	MidiOutMessage(hMidiOut, 0x90, 0x09, 38, 127);		// 通道0x09特指打击乐，38为Acoustic Snare (小鼓)
	ShowAfterSwap(arr,temparr,size,false);	// 交换后（不暂停）
}
void MoveAway(int x0, int y0, int lenarr)
{
	DWORD result;
	char spaces[40];
	int note = notes[(lenarr/r-1)%7] + 12*((lenarr/r-1)/7);
	MidiOutMessage(hMidiOut, 0x90, 0x09, 84, 127);		// 通道0x09特指打击乐（84为Bell Tree铃树）
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*为开音（即播放note），音量最大:127
	Sleep(100);
	COORD coord = {x0, y0};
	sprintf(spaces, "%40s", "");
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 0);				// 黑色
	WriteConsole(hStdOut, spaces, lenarr, &result, NULL);
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127
}
void MoveIn(int x0, int y0, int lentemparr)
{
	DWORD result;
	char str[40];
	int note = notes[(lentemparr/r-1)%7] + 12*((lentemparr/r-1)/7);
	COORD coord = {x0, y0};
	MidiOutMessage(hMidiOut, 0x90, 0x09, 84, 127);		// 通道0x09特指打击乐（84为Bell Tree铃树）
	MidiOutMessage(hMidiOut, 0x90, 0, note, 127);		// 0x9*为开音（即播放note），音量最大:127
	Sleep(100);
	sprintf(str, "%2d%38s", lentemparr/2, "");
	//ReadConsoleOutputCharacter(hStdOut, str, lentemparr/2, coord, &num);
	int color = ((lentemparr/2)==15? 15 : (lentemparr/2) % 15);
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut,  color<<4 | 15-color);
	WriteConsole(hStdOut, str, lentemparr, &result, NULL);
	getch();
	MidiOutMessage(hMidiOut, 0x80, 0, note, 127);		// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127
}
