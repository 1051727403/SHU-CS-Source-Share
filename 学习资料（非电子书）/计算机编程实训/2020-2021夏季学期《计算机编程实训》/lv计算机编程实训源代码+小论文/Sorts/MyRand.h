// MyRand.h		�������Ӹ�˹�ֲ�����̬�ֲ����;��ȷֲ��������
#ifndef MY_RAND_H
#define MY_RAND_H
/*
Box-Muller�ǲ����������һ�ַ�����Box-Muller �㷨������ԭ��ǳ���£������ȴ���൱�򵥡�
�����(0,1]ֵ����������һ�µ��������u1��u2����
����ʹ����������ʽ���е���һ�����һ����̬�ֲ����������z
z = r * cos(��) �� z = r * sin(��)
���� r = sqrt(-2 * ln(u2)), ��= 2 * �� * u1
��z����N(0, 1)�����ͨ�����Ա任
x = m + (z * ��)����N(m, ��^2)��
�μ�https://baike.baidu.com/item/box-muller/4023794?fr=aladdin
*/

double GaussRand(double mean=0, double variance=1);	// ��̬�ֲ�(��˹�ֲ�) mena:��ֵ����ѧ������variance����
double UniformRand(double a=0, double b=1);			// ����[a, b]�ϵľ��ȷֲ�

#endif
