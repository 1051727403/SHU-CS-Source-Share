// Score.h
#ifndef SCORE_H
#define SCORE_H

struct Score
{
	char Id[9];															// 学号，最多存放8个字符
	int Chinese, Math, English, Physics, Chemistry, Total;				// 5门课程成绩及总分

	bool operator< (const Score &s) const { return Total <  s.Total; }	// 重载6个关系运算符函数
	bool operator<=(const Score &s) const { return Total <= s.Total; }	// 使得两个结构体变量之间可以直接进行比较
	bool operator> (const Score &s) const { return Total >  s.Total; }	// 从这6个函数体可见，实际上是比较总分Total
	bool operator>=(const Score &s) const { return Total >= s.Total; }
	bool operator==(const Score &s) const { return Total == s.Total; }
	bool operator!=(const Score &s) const { return Total != s.Total; }
};

void InitScore(Score*, int);										// 设置原始数据
void ShowScore(const Score*, int, int);					// 倒序输出数组的最后last个元素（高分者）
void TestScore(int, int);														// 测试函数

#endif
