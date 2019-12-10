#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main()
{
    list<int> l;
    size_t loc;
    int num;
    cin >> loc;
    while(cin >> num && num >= 0) {
        l.push_back(num);
    }
    if(loc > l.size()) {
        cout << "NULL" << endl;
        return 0;
    }
    auto p = l.rbegin();
    for(;--loc;p++);
    cout << *p << endl;
    return 0;
}