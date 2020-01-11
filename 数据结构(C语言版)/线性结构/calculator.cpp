#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<map>
#include<cmath>

using namespace std;

vector<string> post;

void convert(const string &expr) {
    map<string, size_t> prior;
    stack<string> opt;
    prior["("] = prior[")"] = 1;
    prior["+"] = prior["-"] = 2;
    prior["*"] = prior["/"] = 3;
    size_t len = expr.size();
    for (size_t i = 0; i != len; ++i) {
        string temp = "";
        if (isspace(expr[i])) {
            continue;
        }
        if (((expr[i] == '+' || expr[i] == '-') && (i == 0 || expr[i - 1] == '(')) || isdigit(expr[i])) {
            if (expr[i] != '+') {
                temp += expr[i];
            }
            while (i + 1 != len && (isdigit(expr[i + 1]) || expr[i + 1] == '.')) {
                temp += expr[++i];
            }
            post.push_back(temp);
        } else {
            switch (expr[i]) {
                case '(':
                    opt.push("(");
                    break;
                case ')':
                    while (opt.top() != "(") {
                        post.push_back(opt.top());
                        opt.pop();
                    }
                    opt.pop();
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    while (!opt.empty() && prior[opt.top()] >= prior[temp + expr[i]]) {
                        post.push_back(opt.top());
                        opt.pop();
                    }
                    opt.push(temp + expr[i]);
                    break;
                default:
                    cerr << "ERROR" << endl;
                    exit(0);
            }
        }
    }
    while (!opt.empty()) {
        post.push_back(opt.top());
        opt.pop();
    }
}

double cal(double item1, double item2, const string &opt) {
    if (opt == "+")
        return item2 + item1;
    else if (opt == "-")
        return item2 - item1;
    else if (opt == "*")
        return item2 * item1;
    else {
        if (fabs(item1) < 1e-6) {
            cerr << "ERROR" << endl;
            exit(0);
        }
        return item2 / item1;
    }
}

double solve(const string &expr) {
    convert(expr);
    stack<double> opr;
    size_t len = post.size();
    for (size_t i = 0; i != len; ++i) {
        if (isdigit(post[i][post[i].size() - 1])) {
            opr.push(stod(post[i]));
        } else {
            if (opr.size() < 2) {
                cerr << "ERROR" << endl;
                exit(0);
            } else {
                double item1 = opr.top();
                opr.pop();
                double item2 = opr.top();
                opr.pop();
                opr.push(cal(item1, item2, post[i]));
            }
        }
    }
    if (opr.size() != 1) {
        cerr << "ERROR" << endl;
        exit(0);
    }
    return opr.top();
}

int main() {
    string expr;
    getline(cin, expr);
    double result = solve(expr);
    cout << result << endl;
    return 0;
}
