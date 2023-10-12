// SortShow.h
// ��ע��������ӿ�winmm�����������ѡ�� -lwinmm������ָ����libwinmm�⣩���������£�Debug��Release�������þ���Ҫ��
//      ���˵� | Project | Settings...[Alt+F7] | Link | Libraries:�·��ı༭��������winmm
// ���� ���˵� | Project | Settings...[Alt+F7] | Link | Extra linking options:�·��༭�������� -lwinmm
#ifndef SORTSHOW_H
#define SORTSHOW_H
#include <windows.h>
#include <stdio.h>		// �� <cstdio>

const int N = 16;							// �����������Ԫ�ظ���

// ��Ȼʹ��ȫ�ֱ����ᵼ�¿���ֲ�Ա���Ϊ�˼��ٺ������βΣ��ؽ����������Ƴ�ȫ�ֱ���
// �˴�Ϊ�ⲿ����������
extern HANDLE		 hStdIn, hStdOut;		// ��׼����/����ľ��
extern HMIDIOUT		 hMidiOut;				// MIDI����豸���
extern unsigned char notes[8];				// ����: do,re,mi,fa,sol,la,si
extern int			 array0[N], array[N], temp[N];
extern int			 col1, col2, top, r;	// ������ʾ����ʼ��

// ��������
DWORD MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume);
// Ϊ�������MIDI��׼���� midiOutShortMsg���ú�������Charles Petzold��Windows�������(��ذ�)��
// ��5��[��������],�廪��ѧ������,2010�꣬��22.3.5С���еĴ��루��1042ҳ��

void Init();								// ��ʼ����
void Quit();								// �ر�MIDI�豸
void SetData(int flag=3);					// ����ԭʼ���ݣ�ȡֵ��Χ1~N��flag=1,2,3, ���α�ʾ���򡢵���������ļ����룩
void ReSetData();							// �ָ����ݣ�������array0�е����ݵ��뵽����array�У�
void Start();								// ����ʼ
void Finish();								// �������
void ShowData();							// ��ʾ������

void ShowChar(int x, int y, int bkcolor, int color, char ch);
void ShowText(int x, int y, int bkcolor, int color, const char *str);
void SWAP(int *a, int i, int j);			// �˴���a��һ����array����ݹ��㷨��
void ShowBar(int x, int y, int value, bool blinding=false);
void ShowBars(int x1, int y1, int value1, int x2, int y2, int value2, bool blinding=false);
void MoveBar(int x0, int y0, int len, int x1, int y1);	// ע��len����Ӧ��Ϊ r*value

double gettime(int restart=0);

void Bubble_Sort(int *array, int length);	// ð������
void Select_Sort(int *array, int length);	// ѡ������
void Merge_Sort(int *array, int length);	// �鲢����
void Quick_Sort(int *array, int length);	// ��������
void MoveIn(int x0, int y0, int lentemparr);
void ShowAfterSwap( int *arr,int *temparr,int size,bool blinding);
void SwapTotal(int *arr, int *temparr,int size);
void MoveAway(int x0, int y0, int lenarr);


#endif
