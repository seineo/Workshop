#include<iostream>
#include<stack>
#include<vector>
#include<string>
#include<cmath>
#include<iomanip>
using namespace std;

double cal(double item1,double item2,const string& opt) {
    if(opt == "+")
        return item1 + item2;
    else if(opt == "-")
        return item1 - item2;
    else if(opt == "*")
        return item1 * item2;
    else {
        if(fabs(item2) < 1e-6) {
            cerr << "ERROR" << endl;
            exit(0);
        }
        return item1 / item2;
    }
}

double solve(const vector<string>& exp) {
    stack<double> opr;
    for(int i = exp.size() - 1;i >= 0;--i) {
        if(isdigit(exp[i][exp[i].size() - 1])) {
            opr.push(stod(exp[i]));
        } else {
            if(opr.size() < 2) {
                cerr << "ERROR" << endl;
                exit(0);
            }
            double item1 = opr.top();   opr.pop();
            double item2 = opr.top();   opr.pop();
            opr.push(cal(item1,item2,exp[i]));
        }
    }
    if(opr.size() != 1) {
        cerr << "ERROR" << endl;
        exit(0);
    }
    return opr.top();
}

int main() {
    string comp;
    vector<string> exp;
    while(cin >> comp) {
        exp.push_back(comp);
    }
    cout << fixed << setprecision(1) << solve(exp) << endl;
    return 0;
}
