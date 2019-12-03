#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int vex_num,adj_num;
vector<vector<int>> adjs;
vector<int> low_cost;

void CreateGraph()
{
    int vex1,vex2,weight;
    cin >> vex_num >> adj_num;
    if(adj_num < vex_num - 1) {  //不可能有生成树，直接退出程序
        cout << "-1" << endl;
        exit(0);
    }
    adjs.resize(vex_num);
    for(int i = 0;i != vex_num;++i)
        adjs[i].resize(vex_num);
    for(int i = 0;i != vex_num;++i) {
        for(int j = 0;j != vex_num;++j) {
            if(i == j)
                adjs[i][j] = 0;
            else
                adjs[i][j] = 99999;
        }
    }
    while(adj_num--) {
        cin >> vex1 >> vex2 >> weight;
        adjs[vex1 - 1][vex2 - 1] = weight;
        adjs[vex2 - 1][vex1 - 1] = weight;
    }
}

int Min()
{
    int min = 99999,loc = -1;
    for(int i = 0;i != vex_num;++i) {
        if(low_cost[i] != 0 && low_cost[i] < min) {
            min = low_cost[i];
            loc = i;
        }
    }
    return loc;
}

void Prim()
{
    int total = 0;
    low_cost.push_back(0);
    for(int i = 1;i != vex_num;++i) {
        low_cost.push_back(adjs[0][i]);
    }
    for(int i = 1;i != vex_num;++i) {
        int min = Min();
        if(min < 0) {
            cout << "-1" << endl;
             return;
        }
        total += low_cost[min];
        low_cost[min] = 0;
        for(int j = 0;j != vex_num;++j) {
            if(adjs[min][j] < low_cost[j])
                low_cost[j] = adjs[min][j];
        } 
    }
    if(total > 99999)
        cout << "-1" << endl;
    else
        cout << total << endl;
}

int main()
{
    CreateGraph();
    Prim();
    return 0;
}