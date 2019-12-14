#include<stdio.h>

void SelectionSort(int a[],int len)
{
	for(int i = 0;i != len - 1;++i) {
		int min = i;
		for(int j = i + 1;j != len;++j) {
			if(a[j] < a[min]) {
				min = j;
			}
		}
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

int main()
{
	int a[] = {1,5,4,3,2};
	SelectionSort(a,5);
	for(int i = 0;i != 5;++i) {
		printf("%d ",a[i]);
	}
	return 0;
}