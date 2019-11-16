#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<limits.h>

#define N 5    //叶子结点数目的最大值
#define M 2 * N - 1    //结点总数的最大值

typedef struct {
	int weight;
	int parent;
	int left;
	int right;
}HTNode,HuffmanTree[M + 1];

typedef char* HuffmanCode[N + 1];

void select(HuffmanTree ht, int pos, int* min1,int* min2)
{
	int min1_val = INT_MAX;
	int min2_val = INT_MAX;
	for(int i = 1;i <= pos;++i) {
		if(ht[i].weight < min1_val && ht[i].parent == 0) {
			min2_val = min1_val;
			min1_val = ht[i].weight;
			*min2 = *min1;
			*min1 = i; 
		} 
		else if(ht[i].weight < min2_val && ht[i].parent == 0) {
			min2_val = ht[i].weight;
			*min2 = i;
		}
	}
}

void CreatHuffmanTree(HuffmanTree ht, int nodes[], int n)
{
	for(int i = 1;i <= n;++i) {
		ht[i].weight = nodes[i];
		ht[i].parent = ht[i].left = ht[i].right = 0;
	}
	int m = 2 * n - 1;
	for(int i = n + 1;i <= m;++i) {
		ht[i].weight = 0;
		ht[i].parent = ht[i].left = ht[i].right = 0;
	}
	int min1 = 0, min2 = 0;
	for(int i = n + 1;i <= m;++i) {
		select(ht,i - 1, &min1, &min2);
		ht[i].weight = ht[min1].weight + ht[min2].weight;
		ht[min1].parent = ht[min2].parent = i;
		ht[i].left = min1;
		ht[i].right = min2;
	}
}

void HuffmanEncode(HuffmanTree ht, HuffmanCode hc, int n)
{
	char* encode = (char*)malloc(n * sizeof(char));
	encode[n - 1] = '\0';
	for(int i = 1;i <= n;++i) {
		int start = n - 1;
		int c = i;
		int par = ht[i].parent;
		while(par != 0) {
			--start;
			if(ht[par].left == c) 
				encode[start] = '0';
			else 
				encode[start] = '1';
			c = par;
			par = ht[par].parent;
		}
		hc[i] = (char*)malloc(n * sizeof(char));
		strcpy(hc[i],&encode[start]);
	}
	free(encode);
}

int main()
{
	HuffmanTree ht;
	HuffmanCode hc;
	int n;
	int nodes[N + 1];
	scanf("%d",&n);
	for(int i = 1;i <= n;++i) {
		scanf("%d",&nodes[i]);
	}
	CreatHuffmanTree(ht,nodes,n);
	for(int i = 1;i <= 2 * n - 1;++i)
		printf("%d ",ht[i].weight);
	printf("\n");
	HuffmanEncode(ht,hc,n);
	for(int i = 1;i <= n;++i) {
		printf("%s\n",hc[i]);
		free(hc[i]);
	}
	return 0;
}