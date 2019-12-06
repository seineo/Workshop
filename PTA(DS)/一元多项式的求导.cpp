#include<iostream>
#include<list>
using namespace std;

struct Node {
    Node(int c,int e):coef(c),expo(e){}
    int coef;
    int expo;
};

int main()
{
    int coef,expo;
    list<Node> l;
    while(cin >> coef >> expo) {
        l.push_back({coef,expo});
    }
    l.remove_if([](const Node& i){return i.expo == 0;});
    if(l.empty()) {
        cout << "0 0" << endl;
        return 0;
    }
    for(auto& i : l) {
        i.coef *= i.expo;
        i.expo--;
    }
    bool first = true;
    for(const auto& i : l) {
        if(first) {
            cout << i.coef << " " << i.expo;
            first = false;
        } else {
            cout << " " << i.coef << " " << i.expo;
        }
    }
    return 0;
}