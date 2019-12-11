//reference : https://blog.csdn.net/MoreWindows/article/details/6684558

#include<stdio.h>

void QuickSort(int a[],int left, int right)
{
	if(left < right) {
		int i = left,j = right,x = a[left];
		while(i < j) {
			while(i < j && a[j] > x)
				j--;
			if(i < j) 
				a[i] = a[j];
			while(i < j && a[i] < x)
				i++;
			if(i < j) 
				a[j] = a[i];
		}
		a[i] = x;
		QuickSort(a,left,i - 1);
		QuickSort(a,i + 1,right);
	}
}

int main()
{
	int a[] = {1,4,2,5,3};
	QuickSort(a,0,4);
	for(int i = 0;i != 5;++i) {
		printf("%d ",a[i]);
	}
	return 0;
}