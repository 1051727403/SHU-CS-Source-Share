// Score.h
#ifndef SCORE_H
#define SCORE_H

struct Score
{
	char Id[9];															// ѧ�ţ������8���ַ�
	int Chinese, Math, English, Physics, Chemistry, Total;				// 5�ſγ̳ɼ����ܷ�

	bool operator< (const Score &s) const { return Total <  s.Total; }	// ����6����ϵ���������
	bool operator<=(const Score &s) const { return Total <= s.Total; }	// ʹ�������ṹ�����֮�����ֱ�ӽ��бȽ�
	bool operator> (const Score &s) const { return Total >  s.Total; }	// ����6��������ɼ���ʵ�����ǱȽ��ܷ�Total
	bool operator>=(const Score &s) const { return Total >= s.Total; }
	bool operator==(const Score &s) const { return Total == s.Total; }
	bool operator!=(const Score &s) const { return Total != s.Total; }
};

void InitScore(Score*, int);										// ����ԭʼ����
void ShowScore(const Score*, int, int);					// ���������������last��Ԫ�أ��߷��ߣ�
void TestScore(int, int);														// ���Ժ���

#endif
