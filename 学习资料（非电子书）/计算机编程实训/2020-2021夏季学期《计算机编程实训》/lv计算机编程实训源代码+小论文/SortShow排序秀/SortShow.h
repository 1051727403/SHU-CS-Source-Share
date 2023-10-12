// SortShow.h
// 请注意添加连接库winmm，或添加连接选项 -lwinmm（均意指连接libwinmm库）。方法如下（Debug和Release两种配置均需要）
//      主菜单 | Project | Settings...[Alt+F7] | Link | Libraries:下方的编辑栏中输入winmm
// 或者 主菜单 | Project | Settings...[Alt+F7] | Link | Extra linking options:下方编辑栏中输入 -lwinmm
#ifndef SORTSHOW_H
#define SORTSHOW_H
#include <windows.h>
#include <stdio.h>		// 或 <cstdio>

const int N = 16;							// 待排序数组的元素个数

// 虽然使用全局变量会导致可移植性变差，但为了减少函数的形参，特将下面变量设计成全局变量
// 此处为外部参照型声明
extern HANDLE		 hStdIn, hStdOut;		// 标准输入/输出的句柄
extern HMIDIOUT		 hMidiOut;				// MIDI输出设备句柄
extern unsigned char notes[8];				// 音符: do,re,mi,fa,sol,la,si
extern int			 array0[N], array[N], temp[N];
extern int			 col1, col2, top, r;	// 数据显示的起始列

// 函数声明
DWORD MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume);
// 为方便调用MIDI标准函数 midiOutShortMsg。该函数引自Charles Petzold《Windows程序设计(珍藏版)》
// 第5版[方敏等译],清华大学出版社,2010年，第22.3.5小节中的代码（第1042页）

void Init();								// 初始设置
void Quit();								// 关闭MIDI设备
void SetData(int flag=3);					// 设置原始数据（取值范围1~N。flag=1,2,3, 依次表示正序、倒序、随机序、文件输入）
void ReSetData();							// 恢复数据（将数组array0中的数据导入到数组array中）
void Start();								// 排序开始
void Finish();								// 排序结束
void ShowData();							// 显示数据条

void ShowChar(int x, int y, int bkcolor, int color, char ch);
void ShowText(int x, int y, int bkcolor, int color, const char *str);
void SWAP(int *a, int i, int j);			// 此处的a不一定是array，如递归算法中
void ShowBar(int x, int y, int value, bool blinding=false);
void ShowBars(int x1, int y1, int value1, int x2, int y2, int value2, bool blinding=false);
void MoveBar(int x0, int y0, int len, int x1, int y1);	// 注意len常常应该为 r*value

double gettime(int restart=0);

void Bubble_Sort(int *array, int length);	// 冒泡排序
void Select_Sort(int *array, int length);	// 选择排序
void Merge_Sort(int *array, int length);	// 归并排序
void Quick_Sort(int *array, int length);	// 快速排序
void MoveIn(int x0, int y0, int lentemparr);
void ShowAfterSwap( int *arr,int *temparr,int size,bool blinding);
void SwapTotal(int *arr, int *temparr,int size);
void MoveAway(int x0, int y0, int lenarr);


#endif
