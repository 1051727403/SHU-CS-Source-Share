//SongList.h
#ifndef SONGLIST_H
#define SONGLIST_H
#include "LinkList.h"
#include <iomanip>
class My_songlist;

class Song_inf
{
public:
	Song_inf(string Title="UNKNOWN", string Album="UNKNOWN", string Album_artist="UNKNOWN", string Codec="UNKNOWN", double Length=0.0, double Bit_rate=0.0);                     //设计转换构造函数，使用UNKNOWN或NULL
	void Set(string Title, string Album, string Album_artist, string Codec, double Length, double Bit_rate);                     //对外接口，录入歌曲信息
	operator string() const;        //类型转换运算符
	void Show(ostream& out) const;
	friend ostream& operator<<(ostream& out, const Song_inf& b);
	//输出数据类重载

	friend class My_songlist;       //申明友类
	//int play();

private:
	string title, album, album_artist, codec;                        //title, album, album_artist, codec
	double length, bit_rate;                        //length, bit_rate
};

class My_songlist
{
public:
	My_songlist(string List_title="UNKNOWN", string Intro="NULL", int Song_num=0, double list_length=0.0);                      //转换构造函数，使用UNKNOWN或NULL
	void Set(string List_title, string Intro, int Song_num, double List_length);
	//更改歌单信息 list_title, intro, song_num, list_length
	operator string() const;            //类型转换运算符
	//void AppendSong(const Song_inf& b); //添加歌曲函数
	void Show(ostream& out) const;      //展示歌单函数
	void Set_Intro(const string Intro);					//更改歌单简介
	void Set_Title(const string List_title);			//更改歌单名称
	void Addsong(const Song_inf song);
	friend ostream& operator<<(ostream& out, const My_songlist& u);
	void Showdel();						//展示歌单详细内容
	void ShowCur();
	Node<Song_inf>* Search(const string str);
	Node<Song_inf>* Go(const int id);
	void Set_Song(const Song_inf);						//更改歌曲名称
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
 