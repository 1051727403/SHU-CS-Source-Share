#include<iostream>
using namespace std;
int judgment1(long &a)//乙组判断
{
    if(a%4==0)
        return 1;
    else
        return 0;
}
int judgment2(long &a)//甲组判断
{
    if(a%2==0)
        return 1;
    else
        return 0;
}
int main()
{
    long a[9];
    int i=1,flag1=0,flag2=0,flag3=0;//此处设置3个循环控制标识符
    a[0]=4;
    while(flag3==0)//外层大循环
    {
        while(flag1==0)//倒推法，乙组循环
        {
            a[i]=a[i-1]*5/4+1;
            if(judgment1(a[i])==0)//若不符合规则，重新开始
            {
                a[0]=a[0]+4;
                i=0;
            }
            i++;
            if(i==6)
            {
                if(a[5]%2==0)//可以与甲组循环衔接
                {
                    flag1=1;//跳出乙组循环
                    flag2=0;//进入甲组循环
                }
                else//不符合甲组分桃规则，重新开始
                {
                    a[0]=a[0]+4;
                    i=1;
                }
            }
        }
        while(flag2==0)//倒推法，甲组循环
        {
            a[i]=a[i-1]*3/2+2;
            if(judgment2(a[i])==0)//不符合规则，需要再次进入上一循环
            {
                flag2=1;//跳出甲组循环
                flag1=0;//进入乙组循环
                i=0;
                a[0]=a[0]+4;
            }
            i++;
            if(i==8)//桃子总数不需要满足规则，直接计算
            {
                a[i]=a[i-1]*3/2+2;
                flag2=flag3=1;//跳出本循环和大循环
            }
        }
    }
    cout<<"rest="<<a[0]<<endl;
    cout<<"total="<<a[8]<<endl;//输出结果
    return 0;
}
