#include<stdio.h>
#include<stdlib.h>

// int kFib(int k, int m)    //recursive
// {
// 	if(k < 2 || m < 0)	
// 		return -1;
// 	if(m < k - 1) 
// 		return 0;
// 	else if(m == k - 1 || m == k)	
// 		return 1;
// 	else 
// 		return 2 * kFib(k, m - 1) - kFib(k, m - k - 1);
// }

int kFib(int k, int m)   //nonrecurvie
{
	if(k < 2 || m < 0)	
		return -1;
	if(m < k - 1) 
		return 0;
	else if(m == k - 1 || m == k)	
		return 1;
	else {
		int sum;
		int* temp = (int*)malloc(k * sizeof(int));
		for(int i = 0;i != k - 1;i++)	
			temp[i] = 0;
		temp[k - 1] = 1;
		for(int i = k;i <= m;i++) {
			sum = 0;
			for(int j = 0;j != k;j++)
				sum += temp[j];
			temp[i % k] = sum;
		}
		sum = temp[m % k];
		free(temp);
		return sum;
	}	
}

int main()
{
	printf("%d\n", kFib(3,5));
	return 0;
}