#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>

#define MAX_VERTEX_NUM 20
typedef char vex_type;
typedef int adj_type;

adj_type low_cost[MAX_VERTEX_NUM];
int book[MAX_VERTEX_NUM];

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

void CreateDN(Graph* graph)      //有向图
{
	scanf("%d %d",&graph->vex_num,&graph->adj_num);
	for(int i = 0;i != graph->vex_num;++i) {
		getchar();
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

int Min(Graph* graph)
{
	int min = INT_MAX,loc = -1;
	for(int i = 0;i != graph->vex_num;++i) {
		if(book[i] == 0 && low_cost[i] < min) {  
			min = low_cost[i];
			loc = i;
		}
	}
	return loc;
}

void Dijkstra(Graph* graph,vex_type v)
{
	int loc = LocateVex(graph,v);
	book[loc] = 1;
	for(int i = 0;i != graph->vex_num;++i) {  //初始化路径长度数组
		if(i == loc) {
			low_cost[i] = 0;
		} else {
			low_cost[i] = graph->adjs[loc][i];
		}
	}
	int min_loc;
	for(int i = 1;i != graph->vex_num;++i) {
		min_loc = Min(graph);
		book[min_loc] = 1;
		for(int j = 0;j != graph->vex_num;++j) {
			if(graph->adjs[min_loc][j] < INT_MAX) {   //有边
				if(low_cost[min_loc] + graph->adjs[min_loc][j] < low_cost[j]) {
					low_cost[j] = low_cost[min_loc] + graph->adjs[min_loc][j];
				}
			}
		}
	}
	for(int i = 0;i != graph->vex_num;++i) {
		printf("%d ", low_cost[i]);
	}
	printf("\n");
}

int main()
{
	Graph graph;
	CreateDN(&graph);
	PrintAdjs(&graph);
	Dijkstra(&graph,'0');
	return 0;
}