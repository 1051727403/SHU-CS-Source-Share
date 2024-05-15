#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
class Book
{
    long int num;  //书号
    char bookname[40];  //书名
    char publicname[40];  //出版社
    char name[20];  //作者
public:
    Book()
    {
        num=0;
        bookname[0] =0;
        publicname[0] =0;
        name[0] =0;
    }
    char * Getbookname(void)
    {
        return bookname;
    }
    char * Getpublicname(void)
    {
        return publicname;
    }
    char * Getname(void)
    {
        return name;
    }
    long Getnum(void )
    {
        return num;
    }
    void Setdata(long, char *,char *,char *);
    void Show(void );
    Book(long, char *,char *,char *);
};
void Book::Setdata(long nu, char *bn,char *p,char *n)
{
    num = nu;
    strcpy(bookname,bn);
    strcpy(publicname,p);
    strcpy(name,n);
}
void Book::Show(void )
{
    cout<<"书号:"<<num<<'\t'<<"书名:"<<bookname<<'\t';
    cout<<"出版社:"<<publicname<<'\t'<<"作者:"<<name<<'\n';
}
Book::Book(long nu, char * bp,char *p,char *n)
{
    Setdata(nu, bp, p, n);
}

int main(void)
{
    Book b1,b2;
    long nu;
    char bn[40];  //书名
    char pn[40];  //出版社
    char na[20];  //作者
    ifstream file1;
    ofstream file3;
    char flag = 'y';
    while( flag=='y' ||flag=='Y') //由 flag 控制循环
    {
        cout<<"\t\t 1: 按书名查找一本书!\n";
        cout<<"\t\t 2: 按出版社查找一本书!\n";
        cout<<"\t\t 3: 按作者查找一本书!\n";
        cout<<"\t\t 4: 加入一本新书!\n";
        cout<<"\t\t 5: 输出同一出版社出版的所有书名!\n";
        cout<<"\t\t 6: 输出所有图书的信息!\n";
        cout<<"\t\t 7: 退出!\n 输入选择：";
        int f;
        cin>>f;
        switch(f)
        {
        case 1:
            cout<<"输入要查找的书名：";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//按读方式打开文件
            while(!file1.eof())
            {
                int n;
                file1.read((char *)&b1,sizeof(Book));
                n=file1.gcount();
                if(n==sizeof(Book))
                {
                    if(strcmp(b1.Getpublicname(),bn)==0) //显示书的信息
                        b1.Show();
                }
            }
            file1.close();
            break;
        case 2:
            cout<<"输入要查找的作者：";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//按读方式打开文件
            while(!file1.eof())
            {
                int n;
                file1.read((char *)&b1,sizeof(Book));
                n=file1.gcount();
                if(n==sizeof(Book))
                {
                    if(strcmp(b1.Getname(),bn)==0) //显示书的信息
                        b1.Show();
                }
            }
            file1.close();
            break;
        case 3:
            cout<<"输入要查找的出版社：";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//按读方式打开文件
            while(!file1.eof())
            {
                int n;
                file1.read((char *)&b1,sizeof(Book));
                n=file1.gcount();
                if(n==sizeof(Book))
                {
                    if(strcmp(b1.Getbookname(),bn)==0) //显示书的信息
                        b1.Show();
                }
            }
            file1.close();
            break;
        case 4:
            cout<<"输入书号：";
            cin>>nu;
            cout<<"输入书名：";
            cin>>bn;
            cout<<"输入出版社：";
            cin>>pn;
            cout<<"输入作者：";
            cin>>na;
            b1.Setdata(nu,bn,pn,na);
            file3.open("book.dat",ios::app|ios::binary);//增补方式打开文件
            file3.write((char*)&b1,sizeof(b1));
            file3.close();
            break;
        case 5:
            cout<<"输入出版社的名字：";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//按读方式打开文件
            while(!file1.eof())
            {
                int n;
                while(file1.read((char *)&b1,sizeof(Book)))
                {
                    n=file1.gcount();
                    if(n==sizeof(Book))
                    {
                        if(strcmp(b1.Getpublicname(),bn)==0) //显示书的信息
                            b1.Show();
                    }
                }
            }
            file1.close();
            break;
        case 6:
            cout<< endl << "所有图书信息如下：" << endl;
            cout<<"****************************************************" << endl;
            file1.open("book.dat",ios::in | ios::binary);//按读方式打开文件
            while(!file1.eof())
            {
                int n;
                while(file1.read((char *)&b1,sizeof(Book)))
                {
                    n=file1.gcount();
                    if(n==sizeof(Book))
                    {
                        b1.Show();
                    }
                }
            }
            file1.close();
            break;
        default:
            flag = 'n';
        }
    }
    system("pause");
    return 0;
}
