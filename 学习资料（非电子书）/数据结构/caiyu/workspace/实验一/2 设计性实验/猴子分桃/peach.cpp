#include<iostream>
using namespace std;
int judgment1(long &a)//�����ж�
{
    if(a%4==0)
        return 1;
    else
        return 0;
}
int judgment2(long &a)//�����ж�
{
    if(a%2==0)
        return 1;
    else
        return 0;
}
int main()
{
    long a[9];
    int i=1,flag1=0,flag2=0,flag3=0;//�˴�����3��ѭ�����Ʊ�ʶ��
    a[0]=4;
    while(flag3==0)//����ѭ��
    {
        while(flag1==0)//���Ʒ�������ѭ��
        {
            a[i]=a[i-1]*5/4+1;
            if(judgment1(a[i])==0)//�������Ϲ������¿�ʼ
            {
                a[0]=a[0]+4;
                i=0;
            }
            i++;
            if(i==6)
            {
                if(a[5]%2==0)//���������ѭ���ν�
                {
                    flag1=1;//��������ѭ��
                    flag2=0;//�������ѭ��
                }
                else//�����ϼ�����ҹ������¿�ʼ
                {
                    a[0]=a[0]+4;
                    i=1;
                }
            }
        }
        while(flag2==0)//���Ʒ�������ѭ��
        {
            a[i]=a[i-1]*3/2+2;
            if(judgment2(a[i])==0)//�����Ϲ�����Ҫ�ٴν�����һѭ��
            {
                flag2=1;//��������ѭ��
                flag1=0;//��������ѭ��
                i=0;
                a[0]=a[0]+4;
            }
            i++;
            if(i==8)//������������Ҫ�������ֱ�Ӽ���
            {
                a[i]=a[i-1]*3/2+2;
                flag2=flag3=1;//������ѭ���ʹ�ѭ��
            }
        }
    }
    cout<<"rest="<<a[0]<<endl;
    cout<<"total="<<a[8]<<endl;//������
    return 0;
}
