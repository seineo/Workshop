#include<iostream>
#include<queue>
#include<vector>
#include <assert.h>
using namespace std;

#define MAX_VEX_NUM 20
#define vex_type char

typedef struct {
	vex_type vexs[MAX_VEX_NUM];
	int adj_matrix[MAX_VEX_NUM][MAX_VEX_NUM];
	int vex_num,adj_num;
}Graph;

int GetLocation(Graph* graph,char vex)
{
	for(int i = 0;i != graph->vex_num;++i) {
		if(graph->vexs[i] == vex) {
			return i;
		}
	}
	return -1;
}

void CreatAOV(Graph* graph)
{
	scanf("%d %d",&graph->vex_num,&graph->adj_num);
	for(int i = 0;i != graph->vex_num;++i) {
		getchar();
		scanf("%c",&graph->vexs[i]);
	}
	char start,end;
	int start_loc,end_loc;
	for(int i = 0;i != graph->vex_num;++i) {   
		for(int j = 0;j != graph->vex_num;++j) {
			graph->adj_matrix[i][j] = 0;
		}
	}
	for(int i = 0;i != graph->adj_num;++i) {
		getchar();
		scanf("%c %c",&start,&end);
		start_loc = GetLocation(graph,start);
		end_loc = GetLocation(graph,end);
		assert(start_loc != -1 && end_loc != -1);
		graph->adj_matrix[start_loc][end_loc] = 1;
	}
}

void PrintAdjs(Graph* graph)
{
	for(int i = 0;i != graph->vex_num;++i) {
		for(int j = 0;j != graph->vex_num;++j) {
			printf("%d ", graph->adj_matrix[i][j]);
		}
		printf("\n");
	}
}

void TopoSort(Graph* graph)
{
	queue<int> q;
	vector<int> indegree(graph->vex_num,0);
	for(int i = 0;i != graph->vex_num;++i) {    //计算各节点入度
		for(int j = 0;j != graph->vex_num;++j) {
			indegree[i] += graph->adj_matrix[j][i];
		}
	}
	for(int i = 0;i != graph->vex_num;++i) {  //将入度为0的结点下标入队列
		if(indegree[i] == 0) {
			q.push(i);
		}
	}
	int count_vex = 0;
	while(!q.empty()) {
		count_vex++;
		int cur = q.front();
		q.pop();
		printf("%c ", graph->vexs[cur]);
		for(int i = 0;i != graph->vex_num;++i) {
			if(graph->adj_matrix[cur][i] != 0) {   //将邻接结点的入度-1,若减为0则将该点入队列
				if(--indegree[i] == 0) {
					q.push(i);
				}
			}
		}
	}
	if(count_vex == graph->vex_num) {   //若每一个结点都已输出，则图中无环
		printf("No circle\n");
	} else {
		printf("Have circle(s) \n");
	}
}

int main()
{
	Graph graph;
	CreatAOV(&graph);
	PrintAdjs(&graph);
	TopoSort(&graph);
	return 0;
}