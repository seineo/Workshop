#include<stdio.h>

void BinaryInsertSort(int a[],int n)
{
	for(int i = 1;i != n;++i) {
		int temp = a[i];
		int low = 0;
		int high = i - 1;
		while(low <= high) {
			int mid = (low + high) / 2;
			if(temp > a[mid]) {
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}
		for(int j = i;j > low;--j) {
			a[j] = a[j - 1];
		}
		a[low] = temp;
	}
}

int main()
{
	int a[] = {1,5,4,3,2};
	BinaryInsertSort(a,5);
	for(int i = 0;i != 5;++i) {
		printf("%d ",a[i]);
	}
	return 0;
}