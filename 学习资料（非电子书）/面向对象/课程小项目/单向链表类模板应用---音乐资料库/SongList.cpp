//SongList.cpp
#include "SongList.h"
#include <iomanip>

Song_inf::Song_inf(string Title, string Album, string Album_artist, string Codec, double Length, double Bit_rate)
	: title(Title), album(Album), album_artist(Album_artist), codec(Codec), length(Length), bit_rate(Bit_rate)
{

}

void Song_inf::Set(string Title, string Album, string Album_artist, string Codec, double Length, double Bit_rate)
{
	title = Title;
	album = Album;
	album_artist = Album_artist;
	codec = Codec;
	length = Length;
	bit_rate = Bit_rate;
}

Song_inf::operator string() const
{
	return title;
}

ostream& operator<<(ostream& out, const Song_inf& node)
{
	out << "|" << node.title << "\t\t|"
	    << node.album << "\t\t\t|"
		<< node.album_artist << "\t\t|"
	    << node.length << "\t|"
	    << node.codec << "\t|"
	    << node.bit_rate << "\t|" << endl;
	return out;
}

void Song_inf::Show(ostream& out) const
{
	out << "|" << title << "\t|"
		<< album << "\t|"
		<< album_artist << "\t|"
		<< length << "\t|"
		<< codec << "\t|"
		<< bit_rate << "\t|" << endl;
}

My_songlist::My_songlist(string List_title, string Intro, int Song_num, double List_length)
	: list_title(List_title), intro(Intro), song_num(Song_num), list_length(List_length)
{

}

void My_songlist::Set(string List_title, string Intro, int Song_num, double List_length)
{
	list_title = List_title;
	intro = Intro;
	song_num = Song_num;
	list_length = List_length;
}

My_songlist::operator string() const
{
	return list_title;
}

ostream& operator<<(ostream& out, const My_songlist& node)
{
	
	out	<< setfill(' ') << setw(6) << node.list_title << "\t|" << endl;
	return out;
}

void My_songlist::Show(ostream& out) const
{
	out << "|歌单名\t\t|" << list_title << "\t|" << endl;
	out << "|歌曲数\t\t|" << link.NumNodes() << "\t|" << endl;
	out << "|简介\t\t|" << intro << "\t|" << endl;
	//link.ShowList1();
	//out << "按Enter键返回歌单列表..." << endl;
}

void My_songlist::Set_Title(const string List_title) {
	list_title = List_title;
};

void My_songlist::Set_Intro(const string Intro) {
	intro = Intro;
}

void My_songlist::Showdel()
{
	//cout << "|歌单名\t|" << list_title << "\t|" << endl;
	//cout << "|歌曲数目\t|" << link.NumNodes() << "\t|" << endl;
	//cout << "|简介\t|" << intro << "\t|" << endl;
	link.ShowList1();
	cout << "按Enter键返回歌单列表..." << endl;
}

void My_songlist::Addsong(const Song_inf song)
{
	link.Append(song);
}

void My_songlist::ShowCur() {
	link.CurData().Show(cout);
}

Node<Song_inf> *My_songlist::Search(const string str) {
	return link.Locate(str, 1);
}
 
Node<Song_inf> *My_songlist::Go(const int id) {
	return link.Go(id);
}

void My_songlist::delcurnode() {
	link.DeleteCurNode();
}

void My_songlist::Set_Song(const Song_inf song) {
	link.ModifyData(song);
}

int My_songlist::song_nummm() {
	return link.NumNodes();
}

void My_songlist::ini1() {
	Song_inf	song1("倩女幽魂", "电影歌曲101", "张国荣", "FLAC", 217, 805.0),
		song2("Yellow", "Parachutes", "Coldplay", "FLAC", 269, 1023.0),
		song3("白玫瑰", "What's Going On", "陈奕迅", "MP3", 240, 824.0),
		song4("平凡之路", "猎户星座", "朴树", "FLAC", 302, 882.0),
		song5("Wonderwall", "Stop The Clocks", "Oasis", "FlAC", 259, 1023.0);
	link.Append(song2);
	link.Append(song5);

}

void My_songlist::ini2() {
	Song_inf	song1("倩女幽魂", "电影歌曲101", "张国荣", "FLAC", 217, 805.0),
		song2("Yellow", "Parachutes", "Coldplay", "FLAC", 269, 1023.0),
		song3("白玫瑰", "What's Going On", "陈奕迅", "MP3", 240, 824.0),
		song4("平凡之路", "猎户星座", "朴树", "FLAC", 302, 882.0),
		song5("Wonderwall", "Stop The Clock", "Oasis", "FlAC", 259, 1023.0);
	link.Append(song1);
	link.Append(song3);
	link.Append(song4);

}