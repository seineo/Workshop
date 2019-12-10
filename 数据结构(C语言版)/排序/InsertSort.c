#include<stdio.h>

void InsertSort(int a[],int n)
{
	for(int i = 1;i < n;++i) {
		int temp = a[i];
		int j = 0;
		for(j = i - 1;j >= 0 && a[j] > temp;--j) {
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}

int main()
{
	int a[5] = {1,3,2,5,4};
	InsertSort(a,5);
	for(int i = 0;i != 5;++i) {
		printf("%d ",a[i]);
	}
	return 0;
}