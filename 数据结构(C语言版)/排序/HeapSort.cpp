#include<iostream>
using namespace std;

#define LeftChild(i) (2 * (i) + 1)

void PercDown(int a[],int i,int n)    //筛选：对于左/右子树是堆的完全二叉树，调整根节点使整个树为堆
{
	int child,temp;
	for(temp = a[i];LeftChild(i) < n;i = child) {
		child = LeftChild(i);
		if(child != n - 1 && a[child + 1] > a[child]) 
			child++;
		if(temp < a[child])
			a[i] = a[child];
		else
			break;
	}
	a[i] = temp;
}

void HeapSort(int a[],int n)
{
	for(int i = n / 2;i >= 0;--i)   //建堆 (因为单个结点也是堆，则无序序列建堆的过程可以看作是反复筛选的过程)
		PercDown(a,i,n);
	for(int i = n - 1;i > 0;--i) {
		swap(a[0],a[i]);   //交换第一个元素和最后一个元素（即将最大元素放最后）
		PercDown(a,0,i);   //堆的个数减1了，再次下滤（筛选)
	}
}

int main()
{
	int a[] = {2,5,4,3,1};
	HeapSort(a,5);
	for(int i = 0;i != 5;++i) {
		cout << a[i] << " ";
	}
	return 0;
}