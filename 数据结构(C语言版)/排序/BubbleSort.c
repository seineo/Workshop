#include<stdio.h>

void BubbleSort(int a[],int n)
{
	for(int i = n - 1;i != 0;--i) {
		for(int j = 0;j != i;++j) {
			if(a[j] > a[j + 1]) {
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}

int main()
{
	int a[] = {8,7,10,4,2};
	BubbleSort(a,5);
	for(int i = 0;i != 5;++i) {
		printf("%d ",a[i]);
	}
	return 0;
}