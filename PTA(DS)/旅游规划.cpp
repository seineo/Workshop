#include<iostream>
#include<limits.h>
using namespace std;

struct Info {
    Info() = default;
    Info(int d,int f):distance(d),fare(f){}
    int distance;
    int fare;
};

int book[501];
Info low_cost[501];
Info adjs[501][501];
int vex_num,adj_num,start,dest;

void CreateGraph()
{
    cin >> vex_num >> adj_num >> start >> dest;
    int vex1,vex2,distance,fare;
    for(int i = 0;i != vex_num;++i) {
        for(int j = 0;j != vex_num;++j) {
            if(i == j)
                adjs[i][j] = Info();
            else
                adjs[i][j] = Info(99999,99999);
        }
    }
    while(adj_num--) {
        cin >> vex1 >> vex2 >> distance >> fare;
        adjs[vex1][vex2] = Info(distance,fare);
        adjs[vex2][vex1] = Info(distance,fare);
    }
}

int Min()
{
    int min = INT_MAX,loc;
    for(int i = 0;i != vex_num;++i) {
        if(book[i] == 0 && low_cost[i].distance < min) {
            min = low_cost[i].distance;
            loc = i;
        }
    }
    return loc;
}

void Dijkstra()
{
    for(int i = 0;i != vex_num;++i) {
        if(i != start)
            low_cost[i] = Info(adjs[start][i]);
    }
    low_cost[start] = Info();
    book[start] = 1;
    int min;
    for(int i = 1;i != vex_num;++i) {
        min = Min();
        book[min] = 1;
        for(int j = 0;j != vex_num;++j) {
            if(low_cost[min].distance + adjs[min][j].distance < low_cost[j].distance) 
                low_cost[j] = Info(low_cost[min].distance + adjs[min][j].distance,low_cost[min].fare + adjs[min][j].fare);
            else if(low_cost[min].distance + adjs[min][j].distance == low_cost[j].distance) {
                if(low_cost[min].fare + adjs[min][j].fare < low_cost[j].fare)
                    low_cost[j].fare = low_cost[min].fare + adjs[min][j].fare;
            }
        }
    }
    cout << low_cost[dest].distance << " " << low_cost[dest].fare << endl;
}

int main()
{
    CreateGraph();
    Dijkstra();
    return 0;
}