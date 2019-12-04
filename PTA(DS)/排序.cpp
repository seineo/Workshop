#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n,num;
    vector<int> v;
    cin >> n;
    while(n--) {
        cin >> num;
        v.push_back(num);
    }
    sort(v.begin(),v.end());
    cout << v[0];
    int len = v.size();
    for(int i = 1;i != len;++i) {
        cout << " " << v[i];
    }
    return 0;
}
