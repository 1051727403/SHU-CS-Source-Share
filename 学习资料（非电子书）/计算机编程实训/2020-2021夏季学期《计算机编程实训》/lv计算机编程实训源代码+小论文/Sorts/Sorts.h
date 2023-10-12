// Sorts.h		四种（冒泡、选择、归并、快速）
#ifndef SORTS_H
#define SORTS_H
#include <iostream>
using namespace std;
typedef unsigned long long ULL;

double gettime(int restart=0);

template <typename T> void GetMemory(T*& data, T*& data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{																	// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if (data0 != NULL) delete[] data0;								// 先释放原先所"拥有"的堆空间资源
	if (data != NULL) delete[] data;
	data0 = new T[n];												// 重新申请新的（容量符合要求的）堆空间资源
	data = new T[n];
}

template <typename T> void FreeMemory(T*& data, T*& data0)			// 释放指针所"拥有"的堆空间资源
{
	if (data0 != NULL) delete[] data0;
	if (data != NULL) delete[] data;
	data0 = data = NULL;											// 这一条赋值语句非常重要！保持"隐含约定"
}

template <typename T> void ReSet(T* data, const T* data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	for (int i = 0; i < n; i++) {
		data[i] = data0[i];
	}
}

template <typename T> bool Check(const T* a, int size)				// 检验数组元素是否已按升序排列
{
	for (int i = 1; i < size; i++)
		if (a[i - 1] > a[i])
			{cout << '*' << i << endl;return false;}
	return true;
}
//归并------------------------------------------------------------------------------------------------------------------------------------------------------
//利用插入排序优化
template <typename T> void insertSort(T* arr, int left, int right, ULL& compareCnt, ULL& assignCnt)
{
	for (int i = left + 1; i <= right; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			T temp = arr[i];
			int j = i;
			while (j > left && arr[j - 1] > temp)
			{
				arr[j] = arr[j - 1];
				j--;
				assignCnt++;
				compareCnt++;
			}
			arr[j] = temp;
		}
		compareCnt++;
	}
}
//优化前----------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T> void merge(T* arr, T* temparr, int left, int mid, int right, ULL& compareCnt, ULL& assignCnt)
{
	int i = left;
	int j = mid + 1;
	for (int k = left; k <= right; k++) {//把原数据拷贝到临时数组中
		temparr[k] = arr[k];
		assignCnt++;
	}
	for (int k = left; k <= right; k++) {
		if (i > mid) {
			arr[k] = temparr[j++];
		}
		else if (j > right) {
			arr[k] = temparr[i++];
		}
		else if (temparr[j] < temparr[i]) {
			arr[k] = temparr[j++];
			compareCnt++;
		}
		else {
			arr[k] = temparr[i++];
			compareCnt++;
		}
		assignCnt++;
	}
}
//拆分,需要在调用前创建一个大小与arr相同的空数组，用来零时存放
template <typename T> void _mergeSort(T* arr, T* temparr, int left, int right, ULL& compareCnt, ULL& assignCnt)
{
	if (left >= right)
	{
		return;
	}
	int mid = left + (right - left) / 2;
	_mergeSort(arr, temparr, left, mid, assignCnt, compareCnt);
	_mergeSort(arr, temparr, mid + 1, right, assignCnt, compareCnt);
	merge(arr, temparr, left, mid, right, assignCnt, compareCnt);
}
 //调用函数
 template <typename T> void mergeSort(T* arr, int size, ULL& compareCnt, ULL& assignCnt)
 {
	 T* tempdata = new T[size];
	 _mergeSort(arr, tempdata, 0, size - 1, compareCnt, assignCnt);
	 if (tempdata != NULL) delete[] tempdata;
	 tempdata = NULL;
 }
 //优化后-------------------------------------------------------------------------------------------------------------------------------------------------
 template <typename T>  void _mergePlus(T* arr, T* temparr, int left, int mid, int right, ULL& compareCnt, ULL& assignCnt)
 {
	 int i = left;
	 int j = mid + 1;
	 //此处的临时数组拷贝，通过在递归过程中交换临时数组和原数组得以省略，节约时间
	 for (int k = left; k <= right; k++) {
		 if (i > mid) {
			 arr[k] = temparr[j++]; // 左侧用完，把右侧依次放入
		 }
		 else if (j > right) {
			 arr[k] = temparr[i++]; // 右侧用完，把左侧依次放入
		 }
		 else if (temparr[j] < temparr[i]) {
			 arr[k] = temparr[j++]; // 右边小于左边，把右侧元素放入
			 compareCnt++;
		 }
		 else {
			 arr[k] = temparr[i++]; // 左边小于右边，把左侧元素放入
			 compareCnt++;
		 }
		 assignCnt++;
	 }
 }
//拆分,需要在调用前创建一个大小与arr相同的空数组，用来零时存放
 template <typename T> void _mergeSortPlus(T* arr, T* temparr, int left, int right, ULL& compareCnt, ULL& assignCnt)
 {
	 if (left + 10 >= right)
	 {
		 insertSort(arr, left, right, compareCnt, assignCnt);//小规模数据利用插入算法替代归并算法可以减少栈的使用，防止栈溢出的同时减少空间复杂度
		 return;
	 }
	 int mid = left + (right - left) / 2;
	 _mergeSortPlus(temparr, arr, left, mid, compareCnt, assignCnt);//交换临时数组和原数组节省拷贝时间
	 _mergeSortPlus(temparr, arr, mid + 1, right, compareCnt, assignCnt);
	 //if(temparr[mid]<=temparr[mid+1]&&arr[mid]<=arr[mid+1]) return;//若左右都已排序并左侧均比右侧小，则视为已排序，跳过合并步骤
	 //ps:若使用临时数组互换的操作则if操作失效，因为不知道排序完成的是那个数组，而若另外添加函数来进行判断，则会耗费更多的时间与空间，综合比较后，决定取消此操作。
	 _mergePlus(arr, temparr, left, mid, right, compareCnt, assignCnt);//因为外部_mergeSortPlus和_mergePlus的参数顺序是相同的， 所以，无论递归过程中辅助数组和
																 //原数组的角色如何替换，对最后一次调用的_mergePlus而言,，最终被排为有序的都是原数组，而不是辅助数组！  
 }
 //调用函数
 template <typename T> void mergeSortPlus(T* arr, int size, ULL& compareCnt, ULL& assignCnt)
 {
	 bool a = true;//对完全顺序类型数据进行特判，比较发现并不会占用其他数据类型过多时间，利大于弊
	 for (int i = 0; i < size - 1; i++) {
		 if (arr[i] > arr[i + 1]) { a = false; }
		 compareCnt++;
	 }
	 if (a) { return; }
	 T* temparr = new T[size];
	 for (int i = 0; i < size; i++)//在该阶段时创建临时数组并将原数组的元素拷贝
	 {
		 temparr[i] = arr[i];
	 }
	 _mergeSortPlus(arr, temparr, 0, size - 1, compareCnt, assignCnt);
	 if (temparr != NULL) delete[] temparr;
	 temparr = NULL;
 }
 
 //冒泡----------------------------------------------------------------------------------------------------------------------------------------------
 //未优化的冒泡--------------------------------------------------------------------------------------------------------------------------------------
 template <typename T> void Bubble(T* a, int size, ULL& compareCnt, ULL& assignCnt) {
	 T temp;											// 定义一个局部变量，数据类型与形式数据类型相同
	 int i, j;
	 assignCnt = 0;
	 compareCnt = 0;
	 for (i = 1; i < size; i++)							// 共进行 size-1 轮比较和交换
	 {
		 for (j = 0; j < size - i; j++)
		 {
			 compareCnt++;
			 if (a[j] > a[j + 1])						// 相邻元素之间比较，必要时
			 {
				 temp = a[j];						// 交换 a[j] 与 a[j+1]
				 a[j] = a[j + 1];
				 a[j + 1] = temp;
				 assignCnt += 3;
			 }
		 }
	 }
 }
 
 //已优化的冒泡
 template <typename T> void g_Bubble(T* a, int size, ULL& compareCnt, ULL& assignCnt)//更好的的冒泡
 {
	 T temp;											// 定义一个局部变量，数据类型与形式数据类型相同
	 int left = 0, right = size - 1;
	 bool f = false;                                    //用于标记是否发生交换
	 assignCnt = 0;
	 compareCnt = 0;
	 while (left <= right)					//判断左右边界是否相遇，若相遇则退出
	 {
		 int newleft = left;                       //不断更新数组的左右边界
		 int newright = right;
		 for (int j = left; j < right; ++j)
		 {
			 ++compareCnt;
			 if (a[j] > a[j + 1])
			 {
				 temp = a[j];	           //交换a[j]和a[j+1]
				 a[j] = a[j + 1];
				 a[j + 1] = temp;
				 newright = j;
				 assignCnt += 3;
				 f = true;
			 }
		 }
		 if (!f) return;                        //如果没有发生交换就退出
		 f = false;
		 right = newright;                    //交换右边界
		 for (int j = right; j > left; --j)
		 {
			 compareCnt++;
			 if (a[j - 1] > a[j]) {
				 temp = a[j];	          //交换a[j]和a[j-1]
				 a[j] = a[j - 1];
				 a[j - 1] = temp;
				 newleft = j;
				 assignCnt += 3;
				 f = true;
			 }
		 }
		 if (!f) return;                    //同上
		 left = newleft;                    //交换左边界
	 }
 }
 
//选择----------------------------------------------------------------------------------------------------------------------------------------------
//未优化的选择--------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void Select(T* a, int size, ULL& compareCnt, ULL& assignCnt)	// 选择排序
{
	int i, j, k = 0;
	for (i = 1; i < size; i++)							// 循环size-1次
	{
		for (j = i; j < size; j++)
		{
			if (a[j] < a[k])
				k = j;								// 找出当前范围内"最小"元素的下标
			++compareCnt;
		}
		if (k != i - 1)									// 若"最小"元素不是a[i-1]，则交换之
		{
			swap(a[k], a[i - 1]);
			++assignCnt;
		}
		k = i;
	}
	assignCnt *= 3;
}

//优化的选择
template<typename T>
void Select_Primer(T* a, int size, ULL& compareCnt, ULL& assignCnt)
{
	int left = 0, right = size - 1;					//左右指针分别指向开头和结尾
	while (left < right)
	{
		int minp = left, maxp = right;				//假设指针所在位置即为未排序段的最值
		for (int j = left; j <= right; ++j)			//查找未排序段的最值
		{
			if (a[j] < a[minp]) minp = j;			//记录最小值
			if (a[j] > a[maxp]) maxp = j;			//记录最大值
			compareCnt += 2;
		}
		if (minp != left)							//交换left与最小值
		{
			swap(a[left], a[minp]);
			++assignCnt;
		}
		if (maxp != right && (maxp != left || minp != right))						//交换right与最大值
		{
			maxp == left ? swap(a[minp], a[right]) : swap(a[right], a[maxp]);		//若最大值在原来left的位置则需要重定向
			++assignCnt;
		}
		++left;
		--right;
	}
	assignCnt *= 3;
}

//快排----------------------------------------------------------------------------------------------------------------------------------------------
//未优化的快排--------------------------------------------------------------------------------------------------------------------------------------
template <typename T> void Qsort(T* a, int size, ULL& compareCnt, ULL& assignCnt)	// 快速排序
{
	if (size <= 1) return;
	T pivot;
	int left = 0, right = size - 1;						// 下标（整数）
	pivot = a[right];								// 选择最后一个值为分界值
	do
	{
		while (left < right && a[left] <= pivot)
		{
			left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
			++compareCnt;
		}
		while (left < right && a[right] >= pivot)
		{
			right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
			++compareCnt;
		}
		if (left < right)
		{
			swap(a[left], a[right]);
			assignCnt += 3;
		}
	} while (left < right);
	a[size - 1] = a[left]; a[left] = pivot;			// 找到分界点 left
	Qsort(a, left, compareCnt, assignCnt);									// 递归调用(左侧部分)
	Qsort(a + left + 1, size - left - 1, compareCnt, assignCnt);					// 递归调用(右侧部分)
}



template <typename T> void g_Qsort(T* a, int size, ULL& compareCnt, ULL& assignCnt)
{
	if (size <= 1) return;
	T pivot;
	int left = 0, right = size - 1;
	int mid = size / 2;
	if (a[left] > a[right])
	{
		swap(a[left], a[right]);
		assignCnt += 3;
	}
	if (a[mid] > a[right])
	{
		swap(a[mid], a[right]);
		assignCnt += 3;
	}
	if (a[mid] > a[left])
	{
		swap(a[mid], a[left]);
		assignCnt += 3;
	}
	pivot = a[left];
	do
	{
		while (left < right && a[left] <= pivot)
		{
			left++;
			++compareCnt;
		}
		while (left < right && a[right] >= pivot)
		{
			right--;
			++compareCnt;
		}
		if (left < right)
		{
			swap(a[left], a[right]);
			assignCnt += 3;
		}
	} while (left < right);
	a[0] = a[left - 1]; a[left - 1] = pivot;
	Qsort(a, left - 1, compareCnt, assignCnt);
	Qsort(a + left, size - left, compareCnt, assignCnt);
}

template <typename T> void _sort(T* a, int size, ULL& compareCnt, ULL& assignCnt)
{
	sort(a, a + size);
}

#endif
