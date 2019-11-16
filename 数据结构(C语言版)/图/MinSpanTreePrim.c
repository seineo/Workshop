#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>

#define MAX_VERTEX_NUM 20
typedef char vex_type;
typedef int adj_type;

typedef struct {
	vex_type adj_vex;
	adj_type low_cost;
}closedge[MAX_VERTEX_NUM];

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
	for(int i = 0;i != graph->vex_num;++i) {   //初始化邻接矩阵
		for(int j = 0;j != graph->vex_num;++j) {
			if(i == j) 
				graph->adjs[i][j] = 0;
			else
				graph->adjs[i][j] = INT_MAX;
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

int Min(Graph* graph,closedge ce)
{
	int min = INT_MAX,loc = -1;
	for(int i = 0;i != graph->vex_num;++i) {
		if(ce[i].low_cost > 0 && ce[i].low_cost < min) {
			min = ce[i].low_cost;
			loc = i;
		}
	}
	return loc;
}

void MinSpanTreePrim(Graph* graph,vex_type v,closedge ce)
{
	int loc =LocateVex(graph,v);
	for(int i = 0;i != graph->vex_num;++i) {   //初始化closedge
		if(i != loc) { 
			ce[i].adj_vex = v;
			ce[i].low_cost = graph->adjs[loc][i];
		}
	}
	ce[loc].low_cost = 0;
	for(int i = 1;i != graph->vex_num;++i) {
		int nearest = Min(graph,ce);  //求出最近的结点
		printf("%c->%c\n",ce[nearest].adj_vex,graph->vexs[nearest]);
		ce[nearest].low_cost = 0;
		for(int j = 0;j != graph->vex_num;++j) {
			if(graph->adjs[nearest][j] < ce[j].low_cost) {
				ce[j].low_cost = graph->adjs[nearest][j];
				ce[j].adj_vex = graph->vexs[nearest];
			}
		}
	}
}

int main()
{
	Graph graph;
	closedge ce;
	CreateUDN(&graph);
	PrintAdjs(&graph);
	MinSpanTreePrim(&graph,'A',ce);
	return 0;
}