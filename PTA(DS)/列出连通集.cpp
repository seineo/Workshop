#include<iostream>
#include<vector>
#include<queue>
#include<iterator>
#include<algorithm>
using namespace std;

int vex_num,adj_num;
int adjs[10][10];
vector<int> visited;

void CreateGraph()
{
    int vex1,vex2;
    cin >> vex_num >> adj_num;
    while(adj_num--) {
        cin >> vex1 >> vex2;
        adjs[vex1][vex2] = 1;
        adjs[vex2][vex1] = 1;
    }
}

void DFS(int i)
{
    visited[i] = 1;
    cout << i << " ";
    for(int j = 0;j != vex_num;++j) {
        if(adjs[i][j] && !visited[j]) {
            DFS(j);
        }
    }
}

void DFS_Traverse()
{
    visited.resize(vex_num,0);
    for(int i = 0;i != vex_num;++i) {
        if(!visited[i]) {
            cout << "{ ";
            DFS(i);
            cout << "}" << endl;
        }
    }
}

void BFS_Traverse()
{
    queue<int> q;
    fill(visited.begin(),visited.end(),0);
    for(int i = 0;i != vex_num;++i) {
        if(!visited[i]) {
            visited[i] = 1;
            cout << "{ " << i << " ";
            q.push(i);
            while(!q.empty()) {
                int cur = q.front();
                q.pop();
                for(int j = 0;j != vex_num;++j) {
                    if(adjs[cur][j] && !visited[j]) {
                        visited[j] = 1;
                        cout << j << " ";
                        q.push(j);
                    }
                }
            }
            cout << "}" << endl;
        }
    }
}

int main()
{
    CreateGraph();
    DFS_Traverse();
    BFS_Traverse();
    return 0;
}