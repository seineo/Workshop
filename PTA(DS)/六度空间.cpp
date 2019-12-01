#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;

int vex_num,edge_num;
int adjs[1001][1001];

void CreateGraph()
{  
    int vex1,vex2;
    cin >> vex_num >> edge_num;
    for(int i = 0;i != vex_num;++i) {
        for(int j = 0;j != vex_num;++j) {
            if(i == j) 
                adjs[i][j] = 0;
            else
                adjs[i][j] = 99999;
        }
    }
    while(edge_num--) {
        cin >> vex1 >> vex2;
        adjs[vex1 - 1][vex2 - 1] = 1;
        adjs[vex2 - 1][vex1 - 1] = 1;
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
    for(int col = 0;col != vex_num;++col) {
        int count = 0;
        for(int row = 0;row != vex_num;++row) {
            if(adjs[row][col] <= 6) {
                count++;
            }
        }
        cout << col + 1 << ": " << fixed << setprecision(2) << (static_cast<float>(count) / vex_num) * 100 << "%" << endl;
    }
}

void PrintAdjs()
{
    for(int i = 0;i != vex_num;++i) {
        for(int j = 0;j != vex_num;++j) {
            cout << adjs[i][j] << " ";   
        }
        cout << endl;
    }
}

int main()
{
    CreateGraph();
    Floyd();
    PrintResult();
    return 0;
}