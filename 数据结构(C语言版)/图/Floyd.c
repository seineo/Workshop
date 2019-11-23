#include<stdio.h>
#include<limits.h>
#include<assert.h>

#define MAX_VEX_NUM 20
#define vex_type char

typedef struct {
	vex_type vexs[MAX_VEX_NUM];
	int adjs[MAX_VEX_NUM][MAX_VEX_NUM];
	int vex_num,adj_num;
}Graph;

int LocateVex(Graph* graph,vex_type v)
{
	int loc = -1;
	for(int i = 0;i != graph->vex_num;++i) {
		if(graph->vexs[i] == v) {
			return i;
		}
	}
	return loc;
}

void CreateGraph(Graph* graph)
{
	scanf("%d %d",&graph->vex_num,&graph->adj_num);
	for(int i = 0;i != graph->vex_num;++i) {
		getchar();
		scanf("%c",&graph->vexs[i]);
	}
	for(int i = 0;i != graph->vex_num;++i) {   
		for(int j = 0;j != graph->vex_num;++j) {
			if(i == j) {
				graph->adjs[i][j] = 0;
			} else {
				graph->adjs[i][j] = INT_MAX;
			}
		}
	}
	vex_type vex1,vex2;
	int loc1,loc2,weight;
	for(int i = 0;i != graph->adj_num;++i) {
		getchar();
		scanf("%c %c %d",&vex1,&vex2,&weight);
		loc1 = LocateVex(graph,vex1);
		loc2 = LocateVex(graph,vex2);
		assert(loc1 != -1 && loc2 != -1);
		graph->adjs[loc1][loc2] = weight;
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

void Floyd(Graph* graph)   //注意这里的写法是直接修改邻接矩阵
{
	for(int k = 0;k != graph->vex_num;++k) {    //每次允许在k点中转 看是否缩短路径
		for(int i = 0;i != graph->vex_num;++i) {
			for(int j = 0;j != graph->vex_num;++j) {
				if(graph->adjs[i][k] < INT_MAX && graph->adjs[k][j] < INT_MAX) { //要先判断过k是否有边，不然下面一行的相加有可能溢出变为负数
					if(graph->adjs[i][j] > graph->adjs[i][k] + graph->adjs[k][j]) {  
						graph->adjs[i][j] = graph->adjs[i][k] + graph->adjs[k][j];
					}
				}
			}
		}
	}
}	

int main()
{
	Graph graph;
	CreateGraph(&graph);
	PrintAdjs(&graph);
	Floyd(&graph);
	PrintAdjs(&graph);
	return 0;
}