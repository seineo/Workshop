#include<stdio.h>

void InsertSort(int a[],int n,int start_index,int step)
{
	for(int i = start_index + step;i < n;i += step){
		int temp = a[i];
		int j = i - step;
		for(;j >= 0 && a[j] > a[i];j -= step) {
			a[j + step] = a[j];
		}
		a[j + step] = temp;
	}
}

void Shell(int a[],int n)
{
	int step = n / 2;
	while(step > 0) {
		for(int i = 0;i != step;++i) {   //记住：step为多少，原序列就分为多少组
			InsertSort(a,n,i,step);
		}
		step /= 2;
	}
}

int main()
{
	int a[5] = {1,5,4,3,2};
	Shell(a,5);
	for(int i = 0;i != 5;++i) {
		printf("%d ",a[i]);
	}
	return 0;
}