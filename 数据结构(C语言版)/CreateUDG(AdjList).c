#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX_NUM 20
typedef char vex_type;
typedef int adj_type;

typedef struct Node { 
	int adjvex;     //邻接结点
	adj_type weight;  //权值
	struct Node* next;
}Node;

typedef struct VNode {
	vex_type data;   //结点
	Node* first_next;   
}VNode,AdjList[MAX_VERTEX_NUM];   //邻接表(数组)

typedef struct {
	AdjList vexs;
	int vex_num,adj_num;
}Graph;

void CreateUDG(Graph* graph)
{
	scanf("%d %d",&graph->vex_num,&graph->adj_num);
	for(int i = 0;i != graph->vex_num;++i) {
		getchar();
		scanf("%c",&graph->vexs[i].data);
		graph->vexs[i].first_next = NULL;
	}
	int loc1,loc2,weight;
	for(int i = 0;i != graph->adj_num;++i) {
		scanf("%d %d %d",&loc1,&loc2,&weight);
		Node* node = (Node*)malloc(sizeof(Node));
		node->adjvex = loc2;
		node->weight = weight;
		node->next = graph->vexs[loc1].first_next;
		graph->vexs[loc1].first_next = node;

		node = (Node*)malloc(sizeof(Node));
		node->adjvex = loc1;
		node->weight = weight;
		node->next = graph->vexs[loc2].first_next;
		graph->vexs[loc2].first_next = node;
	}
}

void PrintAdjs(Graph* graph)
{
	for(int i = 0;i != graph->vex_num;++i) {
		printf("%c ", graph->vexs[i].data);
		Node* p = graph->vexs[i].first_next;
		while(p != NULL) {
			printf("%d %d\t",p->adjvex,p->weight);
			p = p->next;
		}
	}
}

int main()
{
	Graph graph;
	CreateUDG(&graph);
	PrintAdjs(&graph);
	return 0;
}