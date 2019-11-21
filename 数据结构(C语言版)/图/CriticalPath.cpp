#include<iostream>
#include<stack>
#include<vector>
#include<limits.h>
#include <assert.h>
#include<algorithm>
using namespace std;

#define MAX_VEX_NUM 20
#define vex_type char

typedef struct {
	vex_type vexs[MAX_VEX_NUM];
	int adj_matrix[MAX_VEX_NUM][MAX_VEX_NUM];
	int vex_num,adj_num;
}Graph;

vector<int> vex_earliest;
stack<int> reverse_topo;

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
	int start_loc,end_loc,weight;
	for(int i = 0;i != graph->vex_num;++i) {   
		for(int j = 0;j != graph->vex_num;++j) {
			graph->adj_matrix[i][j] = 0;
		}
	}
	for(int i = 0;i != graph->adj_num;++i) {
		getchar();
		scanf("%c %c %d",&start,&end,&weight);
		start_loc = GetLocation(graph,start);
		end_loc = GetLocation(graph,end);
		assert(start_loc != -1 && end_loc != -1);
		graph->adj_matrix[start_loc][end_loc] = weight;
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

bool TopoSort(Graph* graph)
{
	stack<int> topo;
	vector<int> indegree(graph->vex_num,0);
	vex_earliest.resize(graph->vex_num,0);    //初始化结点最早开始时间为0
	for(int i = 0;i != graph->vex_num;++i) {    //计算各节点入度
		for(int j = 0;j != graph->vex_num;++j) {
			if(graph->adj_matrix[j][i] > 0) {
				indegree[i]++;
			}
		}
	}
	for(int i = 0;i != graph->vex_num;++i) {  //将入度为0的结点下标入栈
		if(indegree[i] == 0) {
			topo.push(i);
		}
	}
	int count_vex = 0;
	while(!topo.empty()) {
		count_vex++;
		int cur = topo.top();
		reverse_topo.push(cur);   //将弹出的拓扑序列结点压入逆拓扑栈
		topo.pop();
		printf("%c ", graph->vexs[cur]);
		for(int i = 0;i != graph->vex_num;++i) {
			if(graph->adj_matrix[cur][i] != 0) {   //将邻接结点的入度-1,若减为0则将该点入队列
				if(--indegree[i] == 0) {
					topo.push(i);
				}
				if(vex_earliest[cur] + graph->adj_matrix[cur][i] > vex_earliest[i]) { //更新邻接结点的最早开始时间
					vex_earliest[i] = vex_earliest[cur] + graph->adj_matrix[cur][i];
				}
			}
		}
	}
	printf("\n");
	return count_vex == graph->vex_num;  //如果处理节点数等于图内节点数，则是有向无环的AOV
}

void CriticalPath(Graph* graph)
{
	int edge_earliest,edge_latest,cur;
	TopoSort(graph);
	int max_ealiest = *max_element(vex_earliest.begin(),vex_earliest.end());
	vector<int> vex_latest(graph->vex_num,max_ealiest);  //将结点最晚发生时间初始化为终点的最早发生时间
	while(!reverse_topo.empty()) {
		cur = reverse_topo.top();
		reverse_topo.pop();
		for(int i = 0;i != graph->vex_num;++i) {
			if(graph->adj_matrix[cur][i] != 0) {
				if(vex_earliest[i] - graph->adj_matrix[cur][i] < vex_latest[cur])  //更新各结点的最晚发生时间
					vex_latest[cur] = vex_earliest[i] - graph->adj_matrix[cur][i];
			}
		}
	}
	for(int i = 0;i != graph->vex_num;++i) {
		for(int j = 0;j != graph->vex_num;++j) {
			if(graph->adj_matrix[i][j] != 0) {  //计算并比较各活动最早发生时间与最晚发生时间
				edge_earliest = vex_earliest[i];
				edge_latest = vex_latest[j] - graph->adj_matrix[i][j];
				if(edge_earliest == edge_latest) {  //是关键路径
					printf("<v%c,v%c> length: %d\t", graph->vexs[i],graph->vexs[j],graph->adj_matrix[i][j]);
				}
			}
		}
	}
}

int main()
{
	Graph graph;
	CreatAOV(&graph);
	PrintAdjs(&graph);
	printf("\n");
	CriticalPath(&graph);
	printf("\n");
	return 0;
}