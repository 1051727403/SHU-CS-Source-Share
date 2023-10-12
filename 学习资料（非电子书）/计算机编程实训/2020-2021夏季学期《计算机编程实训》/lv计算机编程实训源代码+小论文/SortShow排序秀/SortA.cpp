// SortA.cpp
#include "SortA.h"
#include <conio.h>

void Select_Primer(int* a, int size)
{
	size_t left = 0, right = size - 1;
	while (left < right)
	{
		size_t minp = left, maxp = right;
		ShowText(col1-4, top+minp-1, 0, 15, "︻");
		ShowText(col1-4, top+minp, 0, 15, "min");
		ShowText(col1-4, top+maxp, 0, 15, "max");
		ShowText(col1-4, top+maxp+1, 0, 15, "︼");
		for (size_t j = left; j <= right; ++j)
		{
			ShowBars(col1, top+minp, array[minp], col1, top+j, array[j]);
			if (a[j] < a[minp])
			{
				ShowText(col1-8, top+minp, 0, 15, "       ");
				if (minp == maxp) ShowText(col1-4, top+maxp, 0, 15, "max");
				minp = j;
				minp == maxp ? ShowText(col1-8, top+minp, 0, 15, "max,min") : ShowText(col1-4, top+minp, 0, 15, "min");
			}
			ShowBars(col1, top+maxp, array[maxp], col1, top+j, array[j]);
			if (a[j] > a[maxp])
			{
				ShowText(col1-8, top+maxp, 0, 15, "       ");
				if (minp == maxp) ShowText(col1-4, top+maxp, 0, 15, "min");
				maxp = j;
				minp == maxp ? ShowText(col1-8, top+minp, 0, 15, "max,min") : ShowText(col1-4, top+maxp, 0, 15, "max");
			}
		}
		if (minp != left)
			SWAP(a, left, minp);
		ShowText(col1-4, top+minp, 15, 0, "min");
		if (maxp != right && (maxp != left || minp != right))
			maxp == left ? SWAP(a, minp, right) : SWAP(a, right, maxp);
		ShowText(col1-8, top+minp, 0, 15, "       ");
		ShowText(col1-8, top+maxp, 0, 15, "       ");
		ShowText(col1-8, top+left-1, 0, 15, "       ");
		ShowText(col1-8, top+right+1, 0, 15, "       ");
		++left;
		--right;
	}
}
	
void g_Bubble(int* arry, int size)//更好的的冒泡
{
	int left = 0, right = size - 1;
	bool f=false;                                  //用于标记是否发生交换
	ShowText(col1-4, top+left, 0, 15, "︻");
	ShowText(col1-4, top+right, 0, 15, "︼");
	while(left<=right)					          //判断左右边界是否相遇，若相遇则退出
	{
		int newleft = left;                       //不断更新数组的左右边界
		int newright = right;
		ShowText(col1-8, top+left, 0, 15, "left");
	    ShowText(col1-9, top+right, 0, 15, "right");
		for (int j = left; j < right; ++j)
		{
			if (arry[j] > arry[j + 1])	
			{
				SWAP(array, j, j+1);	           //交换a[j]和a[j+1]
				ShowText(col1-9, top+newright, 0, 15, "     ");
				if(newright==newleft)ShowText(col1-8, top+newleft, 0, 15, "left");//原来的标记会被覆盖
				newright = j;
		        ShowText(col1-9, top+newright, 0, 15, "right");//显示右边界
				f = true;
			}
			else							// 无元素需要交换时，展示曾比较过
				ShowBars(col1, top+j, array[j], col1, top+j+1, array[j+1]);
		}
		ShowText(col1-4, top+right, 0, 15, "  ");
		ShowText(col1-4, top+newright, 0, 15, "︼");
		if (!f) return;                        //如果没有发生交换就退出
		f = false;
		right = newright;                      //交换右边界
		for (int j = right; j > left; --j)
		{
			if (arry[j - 1] > arry[j]) {
				SWAP(array,j-1, j);	          //交换a[j]和a[j-1]
				ShowText(col1-8, top+newleft, 0, 15, "    ");
				if(newright==newleft)ShowText(col1-9, top+newright, 0, 15, "right");//原来的标记会被覆盖
				newleft = j;
				ShowText(col1-8, top+newleft, 0, 15, "left");//显示左边界
				f = true;
			}
			else							// 无元素需要交换时，展示曾比较过
				ShowBars(col1, top+j-1, array[j-1], col1, top+j, array[j]);
		}
		ShowText(col1-4, top+left, 0, 15, "  ");
		ShowText(col1-4, top+newleft, 0, 15, "︻");
		if (!f) return;                    //同上
		left = newleft;                    //交换左边界
	}
}

//归并------------------------------------------------------------------------------------------------------------------------------------------------------
//利用插入排序优化
 void insertSort(int*arr,int left,int right)
{
		for (int i = left+1; i <= right; i++)
            {
                if (arr[i - 1] > arr[i])
                {
                    int temp = arr[i];
                    int j = i;
                    while (j > left && arr[j - 1] > temp)
                    {
                        arr[j] = arr[j - 1];
						SWAP(arr, j, j-1);
                        j--;
                    }
                    arr[j] = temp;
					SWAP(arr,i,j);
                }else {
				ShowBars(col1, top+i, arr[i], col1, top+i-1, arr[i-1]);
				}
            }
}

 //优化后-------------------------------------------------------------------------------------------------------------------------------------------------
void _mergePlus(int *arr,int *temparr, int left,int mid,int right)
{
	
	int i = left;    
    int j = mid+1;
	SwapTotal(arr,temparr,16);
	for(int k=left;k<=right;k++){
		MoveAway(col1, k+top,r*arr[k]);//先移出，再移入
		getch();
	}
	for(int k=left;k<=right;k++){
      if(i>mid){
        arr[k] = temparr[j++]; // 左侧用完，把右侧依次放入
		MoveIn(col1, k+top,r*temparr[j-1]);
	  }else if(j>right){
        arr[k] = temparr[i++]; // 右侧用完，把左侧依次放入
		MoveIn(col1, k+top, r*temparr[i-1]);
      }else if(temparr[j]<temparr[i]){
        arr[k] = temparr[j++]; // 右边小于左边，把右侧元素放入
		MoveIn(col1, k+top, r*temparr[j-1]);
      }else {
        arr[k] = temparr[i++]; // 左边小于右边，把左侧元素放入
		MoveIn(col1, k+top, r*temparr[i-1]);
      }
    }
}
//拆分,需要在调用前创建一个大小与arr相同的空数组，用来零时存放
void _mergeSortPlus(int *arr, int *temparr,int left,int right)
 {
	if(left>=right)
	{
		return ;
	}
	int mid=left+(right-left)/2;
	_mergeSortPlus(temparr,arr,left,mid);
	_mergeSortPlus(temparr,arr,mid+1,right);
	_mergePlus(arr,temparr,left,mid,right);
	SwapTotal(arr,temparr,16);//每次递归结束后再换回来。
 }
 //调用函数
void Merge_Sort_Plus(int* arr, int size)
 {
	 int* temparr = new int[size];
	 	for(int i=0;i<size;i++)
	{
		temparr[i]=arr[i];
		ShowBar(col2, i+top, arr[i]);//展示事先拷贝的数组
	}
	 _mergeSortPlus(arr, temparr, 0, size - 1);
	 if (temparr != NULL) delete[] temparr;
	 temparr = NULL;
 }

