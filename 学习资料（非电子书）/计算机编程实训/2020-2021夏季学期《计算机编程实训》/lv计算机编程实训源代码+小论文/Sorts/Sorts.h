// Sorts.h		���֣�ð�ݡ�ѡ�񡢹鲢�����٣�
#ifndef SORTS_H
#define SORTS_H
#include <iostream>
using namespace std;
typedef unsigned long long ULL;

double gettime(int restart=0);

template <typename T> void GetMemory(T*& data, T*& data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{																	// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if (data0 != NULL) delete[] data0;								// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if (data != NULL) delete[] data;
	data0 = new T[n];												// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	data = new T[n];
}

template <typename T> void FreeMemory(T*& data, T*& data0)			// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if (data0 != NULL) delete[] data0;
	if (data != NULL) delete[] data;
	data0 = data = NULL;											// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

template <typename T> void ReSet(T* data, const T* data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	for (int i = 0; i < n; i++) {
		data[i] = data0[i];
	}
}

template <typename T> bool Check(const T* a, int size)				// ��������Ԫ���Ƿ��Ѱ���������
{
	for (int i = 1; i < size; i++)
		if (a[i - 1] > a[i])
			{cout << '*' << i << endl;return false;}
	return true;
}
//�鲢------------------------------------------------------------------------------------------------------------------------------------------------------
//���ò��������Ż�
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
//�Ż�ǰ----------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T> void merge(T* arr, T* temparr, int left, int mid, int right, ULL& compareCnt, ULL& assignCnt)
{
	int i = left;
	int j = mid + 1;
	for (int k = left; k <= right; k++) {//��ԭ���ݿ�������ʱ������
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
//���,��Ҫ�ڵ���ǰ����һ����С��arr��ͬ�Ŀ����飬������ʱ���
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
 //���ú���
 template <typename T> void mergeSort(T* arr, int size, ULL& compareCnt, ULL& assignCnt)
 {
	 T* tempdata = new T[size];
	 _mergeSort(arr, tempdata, 0, size - 1, compareCnt, assignCnt);
	 if (tempdata != NULL) delete[] tempdata;
	 tempdata = NULL;
 }
 //�Ż���-------------------------------------------------------------------------------------------------------------------------------------------------
 template <typename T>  void _mergePlus(T* arr, T* temparr, int left, int mid, int right, ULL& compareCnt, ULL& assignCnt)
 {
	 int i = left;
	 int j = mid + 1;
	 //�˴�����ʱ���鿽����ͨ���ڵݹ�����н�����ʱ�����ԭ�������ʡ�ԣ���Լʱ��
	 for (int k = left; k <= right; k++) {
		 if (i > mid) {
			 arr[k] = temparr[j++]; // ������꣬���Ҳ����η���
		 }
		 else if (j > right) {
			 arr[k] = temparr[i++]; // �Ҳ����꣬��������η���
		 }
		 else if (temparr[j] < temparr[i]) {
			 arr[k] = temparr[j++]; // �ұ�С����ߣ����Ҳ�Ԫ�ط���
			 compareCnt++;
		 }
		 else {
			 arr[k] = temparr[i++]; // ���С���ұߣ������Ԫ�ط���
			 compareCnt++;
		 }
		 assignCnt++;
	 }
 }
//���,��Ҫ�ڵ���ǰ����һ����С��arr��ͬ�Ŀ����飬������ʱ���
 template <typename T> void _mergeSortPlus(T* arr, T* temparr, int left, int right, ULL& compareCnt, ULL& assignCnt)
 {
	 if (left + 10 >= right)
	 {
		 insertSort(arr, left, right, compareCnt, assignCnt);//С��ģ�������ò����㷨����鲢�㷨���Լ���ջ��ʹ�ã���ֹջ�����ͬʱ���ٿռ临�Ӷ�
		 return;
	 }
	 int mid = left + (right - left) / 2;
	 _mergeSortPlus(temparr, arr, left, mid, compareCnt, assignCnt);//������ʱ�����ԭ�����ʡ����ʱ��
	 _mergeSortPlus(temparr, arr, mid + 1, right, compareCnt, assignCnt);
	 //if(temparr[mid]<=temparr[mid+1]&&arr[mid]<=arr[mid+1]) return;//�����Ҷ��������������Ҳ�С������Ϊ�����������ϲ�����
	 //ps:��ʹ����ʱ���黥���Ĳ�����if����ʧЧ����Ϊ��֪��������ɵ����Ǹ����飬����������Ӻ����������жϣ����ķѸ����ʱ����ռ䣬�ۺϱȽϺ󣬾���ȡ���˲�����
	 _mergePlus(arr, temparr, left, mid, right, compareCnt, assignCnt);//��Ϊ�ⲿ_mergeSortPlus��_mergePlus�Ĳ���˳������ͬ�ģ� ���ԣ����۵ݹ�����и��������
																 //ԭ����Ľ�ɫ����滻�������һ�ε��õ�_mergePlus����,�����ձ���Ϊ����Ķ���ԭ���飬�����Ǹ������飡  
 }
 //���ú���
 template <typename T> void mergeSortPlus(T* arr, int size, ULL& compareCnt, ULL& assignCnt)
 {
	 bool a = true;//����ȫ˳���������ݽ������У��ȽϷ��ֲ�����ռ�������������͹���ʱ�䣬�����ڱ�
	 for (int i = 0; i < size - 1; i++) {
		 if (arr[i] > arr[i + 1]) { a = false; }
		 compareCnt++;
	 }
	 if (a) { return; }
	 T* temparr = new T[size];
	 for (int i = 0; i < size; i++)//�ڸý׶�ʱ������ʱ���鲢��ԭ�����Ԫ�ؿ���
	 {
		 temparr[i] = arr[i];
	 }
	 _mergeSortPlus(arr, temparr, 0, size - 1, compareCnt, assignCnt);
	 if (temparr != NULL) delete[] temparr;
	 temparr = NULL;
 }
 
 //ð��----------------------------------------------------------------------------------------------------------------------------------------------
 //δ�Ż���ð��--------------------------------------------------------------------------------------------------------------------------------------
 template <typename T> void Bubble(T* a, int size, ULL& compareCnt, ULL& assignCnt) {
	 T temp;											// ����һ���ֲ�������������������ʽ����������ͬ
	 int i, j;
	 assignCnt = 0;
	 compareCnt = 0;
	 for (i = 1; i < size; i++)							// ������ size-1 �ֱȽϺͽ���
	 {
		 for (j = 0; j < size - i; j++)
		 {
			 compareCnt++;
			 if (a[j] > a[j + 1])						// ����Ԫ��֮��Ƚϣ���Ҫʱ
			 {
				 temp = a[j];						// ���� a[j] �� a[j+1]
				 a[j] = a[j + 1];
				 a[j + 1] = temp;
				 assignCnt += 3;
			 }
		 }
	 }
 }
 
 //���Ż���ð��
 template <typename T> void g_Bubble(T* a, int size, ULL& compareCnt, ULL& assignCnt)//���õĵ�ð��
 {
	 T temp;											// ����һ���ֲ�������������������ʽ����������ͬ
	 int left = 0, right = size - 1;
	 bool f = false;                                    //���ڱ���Ƿ�������
	 assignCnt = 0;
	 compareCnt = 0;
	 while (left <= right)					//�ж����ұ߽��Ƿ����������������˳�
	 {
		 int newleft = left;                       //���ϸ�����������ұ߽�
		 int newright = right;
		 for (int j = left; j < right; ++j)
		 {
			 ++compareCnt;
			 if (a[j] > a[j + 1])
			 {
				 temp = a[j];	           //����a[j]��a[j+1]
				 a[j] = a[j + 1];
				 a[j + 1] = temp;
				 newright = j;
				 assignCnt += 3;
				 f = true;
			 }
		 }
		 if (!f) return;                        //���û�з����������˳�
		 f = false;
		 right = newright;                    //�����ұ߽�
		 for (int j = right; j > left; --j)
		 {
			 compareCnt++;
			 if (a[j - 1] > a[j]) {
				 temp = a[j];	          //����a[j]��a[j-1]
				 a[j] = a[j - 1];
				 a[j - 1] = temp;
				 newleft = j;
				 assignCnt += 3;
				 f = true;
			 }
		 }
		 if (!f) return;                    //ͬ��
		 left = newleft;                    //������߽�
	 }
 }
 
//ѡ��----------------------------------------------------------------------------------------------------------------------------------------------
//δ�Ż���ѡ��--------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void Select(T* a, int size, ULL& compareCnt, ULL& assignCnt)	// ѡ������
{
	int i, j, k = 0;
	for (i = 1; i < size; i++)							// ѭ��size-1��
	{
		for (j = i; j < size; j++)
		{
			if (a[j] < a[k])
				k = j;								// �ҳ���ǰ��Χ��"��С"Ԫ�ص��±�
			++compareCnt;
		}
		if (k != i - 1)									// ��"��С"Ԫ�ز���a[i-1]���򽻻�֮
		{
			swap(a[k], a[i - 1]);
			++assignCnt;
		}
		k = i;
	}
	assignCnt *= 3;
}

//�Ż���ѡ��
template<typename T>
void Select_Primer(T* a, int size, ULL& compareCnt, ULL& assignCnt)
{
	int left = 0, right = size - 1;					//����ָ��ֱ�ָ��ͷ�ͽ�β
	while (left < right)
	{
		int minp = left, maxp = right;				//����ָ������λ�ü�Ϊδ����ε���ֵ
		for (int j = left; j <= right; ++j)			//����δ����ε���ֵ
		{
			if (a[j] < a[minp]) minp = j;			//��¼��Сֵ
			if (a[j] > a[maxp]) maxp = j;			//��¼���ֵ
			compareCnt += 2;
		}
		if (minp != left)							//����left����Сֵ
		{
			swap(a[left], a[minp]);
			++assignCnt;
		}
		if (maxp != right && (maxp != left || minp != right))						//����right�����ֵ
		{
			maxp == left ? swap(a[minp], a[right]) : swap(a[right], a[maxp]);		//�����ֵ��ԭ��left��λ������Ҫ�ض���
			++assignCnt;
		}
		++left;
		--right;
	}
	assignCnt *= 3;
}

//����----------------------------------------------------------------------------------------------------------------------------------------------
//δ�Ż��Ŀ���--------------------------------------------------------------------------------------------------------------------------------------
template <typename T> void Qsort(T* a, int size, ULL& compareCnt, ULL& assignCnt)	// ��������
{
	if (size <= 1) return;
	T pivot;
	int left = 0, right = size - 1;						// �±꣨������
	pivot = a[right];								// ѡ�����һ��ֵΪ�ֽ�ֵ
	do
	{
		while (left < right && a[left] <= pivot)
		{
			left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
			++compareCnt;
		}
		while (left < right && a[right] >= pivot)
		{
			right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
			++compareCnt;
		}
		if (left < right)
		{
			swap(a[left], a[right]);
			assignCnt += 3;
		}
	} while (left < right);
	a[size - 1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	Qsort(a, left, compareCnt, assignCnt);									// �ݹ����(��ಿ��)
	Qsort(a + left + 1, size - left - 1, compareCnt, assignCnt);					// �ݹ����(�Ҳಿ��)
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
