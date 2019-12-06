#include<iostream>
#include<queue>
using namespace std;

int main()
{
    queue<int> a;
    queue<int> b;
    int n,customer,count;
    cin >> n;
    while(n--) {
        cin >> customer;
        if(customer % 2 != 0)
            a.push(customer);
        else
            b.push(customer);
    }
    bool first = true;
    while(!a.empty() && !b.empty()) {
        count = 2;
        while(count-- && !a.empty()) {
            if(first == true) {
                cout << a.front();
                first = false;
            } else {
                cout << " " << a.front();
            }
            a.pop();
        }
        cout << " " << b.front();
        b.pop();
    }
    while(!a.empty()) {
        if(first == true) {
            cout << a.front();
            first = false;
        } else {
            cout << " " << a.front();
        }
        a.pop();
    }
    while(!b.empty()) {
        if(first == true) {
            cout << b.front();
            first = false;
        } else {
            cout << " " << b.front();
        }
        b.pop();
    }
    return 0;
}