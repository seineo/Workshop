#include<iostream>
#include<array>
#include <limits.h>
#include<algorithm>
using namespace std;

array<int,1001> heap;
int size;

void Initializate()
{
    size = 0;
    heap[0] = INT_MIN;
}

void Insert(int elem)
{
    int i;
    for(i = ++size;heap[i / 2] > elem;i /= 2)
        heap[i] = heap[i / 2];
    heap[i] = elem;
}

int main()
{
    int elem_num,path_num,elem,loc;
    cin >> elem_num >> path_num;
    Initializate();
    for(int i = 0;i != elem_num;++i) {
        cin >> elem;
        Insert(elem);
    }
    for(int i = 0;i != path_num;++i) {
        cin >> loc;
        cout << heap[loc];
        while(loc > 1) {
            loc /= 2;
            cout << " " << heap[loc];
        }
        cout << endl;
    }
    return 0;
}