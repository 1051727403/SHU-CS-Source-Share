#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
class Book
{
    long int num;  //���
    char bookname[40];  //����
    char publicname[40];  //������
    char name[20];  //����
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
    cout<<"���:"<<num<<'\t'<<"����:"<<bookname<<'\t';
    cout<<"������:"<<publicname<<'\t'<<"����:"<<name<<'\n';
}
Book::Book(long nu, char * bp,char *p,char *n)
{
    Setdata(nu, bp, p, n);
}

int main(void)
{
    Book b1,b2;
    long nu;
    char bn[40];  //����
    char pn[40];  //������
    char na[20];  //����
    ifstream file1;
    ofstream file3;
    char flag = 'y';
    while( flag=='y' ||flag=='Y') //�� flag ����ѭ��
    {
        cout<<"\t\t 1: ����������һ����!\n";
        cout<<"\t\t 2: �����������һ����!\n";
        cout<<"\t\t 3: �����߲���һ����!\n";
        cout<<"\t\t 4: ����һ������!\n";
        cout<<"\t\t 5: ���ͬһ������������������!\n";
        cout<<"\t\t 6: �������ͼ�����Ϣ!\n";
        cout<<"\t\t 7: �˳�!\n ����ѡ��";
        int f;
        cin>>f;
        switch(f)
        {
        case 1:
            cout<<"����Ҫ���ҵ�������";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//������ʽ���ļ�
            while(!file1.eof())
            {
                int n;
                file1.read((char *)&b1,sizeof(Book));
                n=file1.gcount();
                if(n==sizeof(Book))
                {
                    if(strcmp(b1.Getpublicname(),bn)==0) //��ʾ�����Ϣ
                        b1.Show();
                }
            }
            file1.close();
            break;
        case 2:
            cout<<"����Ҫ���ҵ����ߣ�";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//������ʽ���ļ�
            while(!file1.eof())
            {
                int n;
                file1.read((char *)&b1,sizeof(Book));
                n=file1.gcount();
                if(n==sizeof(Book))
                {
                    if(strcmp(b1.Getname(),bn)==0) //��ʾ�����Ϣ
                        b1.Show();
                }
            }
            file1.close();
            break;
        case 3:
            cout<<"����Ҫ���ҵĳ����磺";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//������ʽ���ļ�
            while(!file1.eof())
            {
                int n;
                file1.read((char *)&b1,sizeof(Book));
                n=file1.gcount();
                if(n==sizeof(Book))
                {
                    if(strcmp(b1.Getbookname(),bn)==0) //��ʾ�����Ϣ
                        b1.Show();
                }
            }
            file1.close();
            break;
        case 4:
            cout<<"������ţ�";
            cin>>nu;
            cout<<"����������";
            cin>>bn;
            cout<<"��������磺";
            cin>>pn;
            cout<<"�������ߣ�";
            cin>>na;
            b1.Setdata(nu,bn,pn,na);
            file3.open("book.dat",ios::app|ios::binary);//������ʽ���ļ�
            file3.write((char*)&b1,sizeof(b1));
            file3.close();
            break;
        case 5:
            cout<<"�������������֣�";
            cin>>bn;
            file1.open("book.dat",ios::in | ios::binary);//������ʽ���ļ�
            while(!file1.eof())
            {
                int n;
                while(file1.read((char *)&b1,sizeof(Book)))
                {
                    n=file1.gcount();
                    if(n==sizeof(Book))
                    {
                        if(strcmp(b1.Getpublicname(),bn)==0) //��ʾ�����Ϣ
                            b1.Show();
                    }
                }
            }
            file1.close();
            break;
        case 6:
            cout<< endl << "����ͼ����Ϣ���£�" << endl;
            cout<<"****************************************************" << endl;
            file1.open("book.dat",ios::in | ios::binary);//������ʽ���ļ�
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
