#include<stdio.h>

void InsertionSort(int a[],int n,int start,int step)
{
	for(int i = start + step;i < n;i += step) {
		int temp = a[i];
		int j = i - step;
		for(;j >= 0 && a[j] > temp;j -= step)
			a[j + step] = a[j];
		a[j + step] = temp;
	}
}

void Shell(int a[],int n)
{
	int step = n / 2;
	while(step > 0) {
		for(int i = 0;i != step;++i) 
			InsertionSort(a,n,i,step);
		step /= 2;
	}
}

int main()
{
	int a[] = {1,5,4,3,2};
	Shell(a,5);
	for(int i = 0;i != 5;++i) 
		printf("%d ",a[i]);
	return 0;
}