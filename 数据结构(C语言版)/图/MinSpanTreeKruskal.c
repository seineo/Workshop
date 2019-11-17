#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <limits.h>

#define MAX_VERTEX_NUM 20
#define INFINITY INT_MAX
typedef char vex_type;
typedef int adj_type;

typedef struct {
	vex_type start;  //起点
	vex_type end; 	//终点
	adj_type weight; 
}Edge;

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
			if(i == j) {
				graph->adjs[i][j] = 0;
			} else {
				graph->adjs[i][j] = INFINITY;
			}
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

Edge* GetEdges(Graph* graph)   //获取所有的边，只取邻接矩阵上三角！
{
	int index = 0;
	Edge* edges = (Edge*)malloc(graph->adj_num * sizeof(Edge));
	for(int i = 0;i != graph->vex_num;++i) {
		for(int j = i + 1;j != graph->vex_num;++j) {
			if(graph->adjs[i][j] != INFINITY) {
				edges[index].start = graph->vexs[i];
				edges[index].end = graph->vexs[j];
				edges[index].weight = graph->adjs[i][j];
				index++;
			}
		}
	}
	return edges;
}

void SortEdges(Edge* edges,Graph* graph)
{
	Edge temp;
	for(int i = graph->adj_num - 1;i != 0;--i) {
		for(int j = 0;j != i;++j) {
			if(edges[j].weight > edges[j + 1].weight){	
				temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
		}
	}
}

Edge* Kruskal(Graph* graph)
{
	int index = 0;
	int loc1,loc2;
	int vex_end[MAX_VERTEX_NUM];
	for(int i = 0;i != graph->vex_num;++i)
		vex_end[i] = i;
	Edge* result = (Edge*)malloc((graph->vex_num - 1) * sizeof(Edge));
	Edge* edges = GetEdges(graph);
	SortEdges(edges,graph);
	for(int i = 0;i != graph->adj_num;++i) {
		loc1 = LocateVex(graph,edges[i].start);
		loc2 = LocateVex(graph,edges[i].end);
		if(vex_end[loc1] != vex_end[loc2]) {
			vex_end[loc1] = loc2;
			result[index++] = edges[i];
		}
	}
	free(edges);
	return result;
}

int main()
{
	Graph graph;
	Edge* result;
	CreateUDN(&graph);
	result = Kruskal(&graph);
	for(int i = 0;i != graph.vex_num - 1;++i) {
		printf("%c-> %c\n", result[i].start,result[i].end);
	}
	free(result);
	return 0;
}