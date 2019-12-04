#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

int main()
{
    unordered_map<string,string> m;
    string account,password;
    char command;
    int num;
    cin >> num;
    while(num--) {
        cin >> command >> account >> password;
        if(command == 'N') {
            if(m.find(account) != m.end()) {
                cout << "ERROR: Exist" << endl;
            } else {
                m.insert({account,password});
                cout << "New: OK" << endl;
            }
        } else {
            auto p = m.find(account);
            if(p == m.end()) {
                cout << "ERROR: Not Exist" << endl;
            } else {
                if(p->second == password) {
                    cout << "Login: OK" << endl;
                } else {
                    cout << "ERROR: Wrong PW" << endl;
                }
            }
        }
    }
    return 0;
}