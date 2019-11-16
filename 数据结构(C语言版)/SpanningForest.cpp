#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX_NUM 20

typedef char ElemType;
typedef char vex_type;
typedef int adj_type;

typedef enum{FALSE,TRUE} BOOLEAN;
BOOLEAN Visited[MAX_VERTEX_NUM];

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

typedef struct TreeNode {
	ElemType data;
	struct TreeNode* first_child,*next_sibling;
}TreeNode,*Tree;

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
	printf("\n");
}

void DFSTree(Graph* graph,int loc,Tree t)
{
	Visited[loc] = TRUE;
	BOOLEAN first = TRUE;
	Node* the_next = graph->vexs[loc].first_next;
	Tree p,q;
	while(the_next != NULL) {
		if(!Visited[the_next->adjvex]) {
			p = (Tree)malloc(sizeof(TreeNode));
			p->data = graph->vexs[the_next->adjvex].data;
			p->first_child = p->next_sibling = NULL;
			if(first) {  //是第一个邻接结点
				t->first_child = p;
				first = FALSE;
			} else {
				q->next_sibling = p;
			}
			q = p;
			DFSTree(graph,the_next->adjvex,p);
		}
		the_next = the_next->next;
	}
}

void DFSForest(Graph* graph,Tree& t)
{
	t = NULL;
	Tree q;
	for(int i = 0;i != graph->vex_num;++i) 
		Visited[i] = FALSE;
	for(int i = 0;i != graph->vex_num;++i) {
		if(!Visited[i]) {
			Tree p = (Tree)malloc(sizeof(TreeNode));
			p->data = graph->vexs[i].data;
			p->first_child = p->next_sibling = NULL;
			if(!t) 
				t = p;
			else
				q->next_sibling = p;
			q = p;
			DFSTree(graph,i,p);
		}
	}
}


void PrintTree(Tree t)
{
	if(t != NULL) {
		printf("%c ", t->data);
		PrintTree(t->first_child);
		PrintTree(t->next_sibling);
	}
}

int main()
{
	Graph graph;
	Tree t;
	CreateUDG(&graph);
	DFSForest(&graph,t);
	PrintTree(t);
	return 0;
}
