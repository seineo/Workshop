#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int vex_num,edge_num;
vector<vector<int>> adjs;

void CreateGraph()
{
    int vex1,vex2,weight;
    cin >> vex_num >> edge_num;
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
    while(edge_num--) {
        cin >> vex1 >> vex2 >> weight;
        adjs[vex1 - 1][vex2 - 1] = weight;
        adjs[vex2 - 1][vex1 - 1] = weight;
    }
}   

void Floyd()
{
    for(int k = 0;k != vex_num;++k) {
        for(int i = 0;i != vex_num;++i) {
            for(int j = 0;j != vex_num;++j) {
                if(adjs[i][k] + adjs[k][j] < adjs[i][j])
                    adjs[i][j] = adjs[i][k] + adjs[k][j];
            }
        }
    }
}

void PrintResult()
{
    vector<int> max_len;
    for(int i = 0;i != vex_num;++i) {
        int cur_max = *max_element(adjs[i].begin(),adjs[i].end());
        max_len.push_back(cur_max);
    }
    auto min_p = min_element(max_len.begin(),max_len.end());
    int min = *min_p;
    if(min == 99999) {
        cout << "0" << endl;
    } else {
        cout << distance(max_len.begin(),min_p) + 1 << " " << min << endl;
    }
}

int main()
{
    CreateGraph();
    Floyd();
    PrintResult();
    return 0;
}