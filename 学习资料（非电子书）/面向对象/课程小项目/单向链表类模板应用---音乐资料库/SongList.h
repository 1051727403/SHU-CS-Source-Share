//SongList.h
#ifndef SONGLIST_H
#define SONGLIST_H
#include "LinkList.h"
#include <iomanip>
class My_songlist;

class Song_inf
{
public:
	Song_inf(string Title="UNKNOWN", string Album="UNKNOWN", string Album_artist="UNKNOWN", string Codec="UNKNOWN", double Length=0.0, double Bit_rate=0.0);                     //���ת�����캯����ʹ��UNKNOWN��NULL
	void Set(string Title, string Album, string Album_artist, string Codec, double Length, double Bit_rate);                     //����ӿڣ�¼�������Ϣ
	operator string() const;        //����ת�������
	void Show(ostream& out) const;
	friend ostream& operator<<(ostream& out, const Song_inf& b);
	//�������������

	friend class My_songlist;       //��������
	//int play();

private:
	string title, album, album_artist, codec;                        //title, album, album_artist, codec
	double length, bit_rate;                        //length, bit_rate
};

class My_songlist
{
public:
	My_songlist(string List_title="UNKNOWN", string Intro="NULL", int Song_num=0, double list_length=0.0);                      //ת�����캯����ʹ��UNKNOWN��NULL
	void Set(string List_title, string Intro, int Song_num, double List_length);
	//���ĸ赥��Ϣ list_title, intro, song_num, list_length
	operator string() const;            //����ת�������
	//void AppendSong(const Song_inf& b); //��Ӹ�������
	void Show(ostream& out) const;      //չʾ�赥����
	void Set_Intro(const string Intro);					//���ĸ赥���
	void Set_Title(const string List_title);			//���ĸ赥����
	void Addsong(const Song_inf song);
	friend ostream& operator<<(ostream& out, const My_songlist& u);
	void Showdel();						//չʾ�赥��ϸ����
	void ShowCur();
	Node<Song_inf>* Search(const string str);
	Node<Song_inf>* Go(const int id);
	void Set_Song(const Song_inf);						//���ĸ�������
	void delcurnode();
	int song_nummm();
	void ini1();
	void ini2();
private:
	string list_title, intro;
	int song_num;
	double list_length;
	LinkList<Song_inf> link;
}; 
#endif // !SONGLIST_H
 