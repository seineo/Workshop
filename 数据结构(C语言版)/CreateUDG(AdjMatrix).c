#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAX_VERTEX_NUM 20
typedef char vex_type;
typedef int adj_type;

typedef struct {
	vex_type vexs[MAX_VERTEX_NUM];   //顶点数组
	adj_type adjs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
	int vex_num,adj_num;
}Graph;

int LocateVex(Graph* graph,vex_type v)
{
	for(int i = 0;i != graph->vex_num;++i) {
		if(graph->vexs[i] == v) {
			return i;
		}
	}
	return -1;
}

void CreateUDN(Graph* graph)    
{
	scanf("%d %d",&graph->vex_num,&graph->adj_num);
	getchar();
	for(int i = 0;i != graph->vex_num;++i) {
		scanf("%c",&graph->vexs[i]);
	}
	for(int i = 0;i != graph->vex_num;++i) {   //初始化邻接矩阵 权值为0
		for(int j = 0;j != graph->vex_num;++j) {
			graph->adjs[i][j] = 0;
		}
	}
	vex_type vex1,vex2;
	int weight; 
	for(int i = 0;i != graph->adj_num;++i) {  //构造邻接矩阵
		getchar();
		scanf("%c %c %d",&vex1,&vex2,&weight);
		int loc1 = LocateVex(graph,vex1);
		int loc2 = LocateVex(graph,vex2);
		assert(loc1 != -1 && loc2 != -1);
		graph->adjs[loc1][loc2] = weight;
		graph->adjs[loc2][loc1] = weight;
	}
}

void PrintAdjs(Graph* graph)
{
	for(int i = 0;i != graph->vex_num;++i) {
		for(int j = 0;j != graph->vex_num;++j) {
			printf("%d ", graph->adjs[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	Graph graph;
	CreateUDN(&graph);
	PrintAdjs(&graph);
	return 0;
}