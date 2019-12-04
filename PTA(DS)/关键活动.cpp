#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include <algorithm>
using namespace std;

struct Node {
    Node(int v):vex(v),flag(false){}
    int vex;
    bool flag;   //用于判断是否是关键活动
};

vector<int> vex_earliest;
vector<int> indegree;
map<int,vector<Node>> critical_activity;
stack<int> rev_topo;
int adjs[101][101];
int vex_num,adj_num;

void CreateGraph()
{
    int vex1,vex2,weight;
    cin >> vex_num >> adj_num;
    while(adj_num--) {
        cin >> vex1 >> vex2 >> weight;
        adjs[vex1 - 1][vex2 - 1] = weight;
        critical_activity[vex1 - 1].push_back(Node(vex2 - 1));
    }
    for(auto& i : critical_activity) {    //将输入顺序的结点逆序，因为题目要求在起点相同时输出要与输入顺序相反
        reverse(i.second.begin(),i.second.end());
    }
}

bool TopoSort()
{
    stack<int> topo;
    indegree.resize(vex_num,0);
    vex_earliest.resize(vex_num,0);
    for(int col = 0;col != vex_num;++col) {
        for(int row = 0;row != vex_num;++row) {
            if(adjs[row][col] != 0) {
                indegree[col]++;
            }
        }
    }
    for(int i = 0;i != vex_num;++i) {
        if(indegree[i] == 0) {
            topo.push(i);
        }
    }
    int count = 0;
    while(!topo.empty()) {
        count++;
        int cur = topo.top();
        rev_topo.push(cur);
        topo.pop();
        for(int i = 0;i != vex_num;++i) {
            if(adjs[cur][i] != 0) {
                if(--indegree[i] == 0)
                    topo.push(i);
                if(vex_earliest[cur] + adjs[cur][i] > vex_earliest[i])
                    vex_earliest[i] = vex_earliest[cur] + adjs[cur][i];
            }
        }
    }
    return count == vex_num;
}

void CriticalPath()
{
    int edge_earliest,edge_lastest;
    int max_time = *max_element(vex_earliest.begin(),vex_earliest.end());
    vector<int> vex_lastest(vex_num,max_time);
    while(!rev_topo.empty()) {
        int cur = rev_topo.top();
        rev_topo.pop();
        for(int i = 0;i != vex_num;++i) {
            if(adjs[cur][i] != 0) {
                if(vex_lastest[i] - adjs[cur][i] < vex_lastest[cur])
                    vex_lastest[cur] = vex_lastest[i] - adjs[cur][i];
            }
        }
    }
    for(int i = 0;i != vex_num;++i) {
        for(int j = 0;j != vex_num;++j) {
            if(adjs[i][j] != 0) {
                edge_earliest = vex_earliest[i];
                edge_lastest = vex_lastest[j] - adjs[i][j];
                if(edge_earliest == edge_lastest) {
                    auto p = find_if(critical_activity[i].begin(),critical_activity[i].end(),
                        [j](const Node& i){return i.vex == j;});  //找到对应结点，将其flag置1
                    p->flag = true;
                }
            }
        }
    }
    cout << max_time << endl;
    for(const auto& i : critical_activity) {
        for(const auto & j : i.second) {
            if(j.flag == true) {  //将关键活动输出
                cout << i.first + 1 << "->" << j.vex + 1 << endl;
            }
        }
    }
}

int main()
{
    CreateGraph();
    if(!TopoSort()) {
        cout << "0" << endl;
    } else {
        CriticalPath();
    }
    return 0;
}