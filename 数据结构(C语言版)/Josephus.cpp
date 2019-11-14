#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int num;
	int code;
	struct Node* next;
}Node, *List;

List CreateList(int n)
{
	int code;
	List head = (List)malloc(sizeof(Node));
	List ret = head;
	for(int i = 1;i <= n;++i) {
		scanf("%d",&code);
		head->next = (List)malloc(sizeof(Node));
		head->next->num = i;
		head->next->code = code;
		head = head->next;
	}
	head->next = ret->next;
	return ret;
}

void PrintSequence(List l,int m,int n)
{
	List pre = l;
	List to_del = l->next;
	int count = n;
	while(count != 0) {
		while(--m) {
			to_del = to_del->next;
			pre = pre->next;
		}
		printf("%d ", to_del->num);
		m = to_del->code;
		pre->next = to_del->next;
		free(to_del);
		to_del = pre->next;
		count--;
	}
}
int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	List l = CreateList(n);
	PrintSequence(l,m,n);
	return 0;
}