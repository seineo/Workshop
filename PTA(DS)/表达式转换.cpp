#include<iostream>
#include<string>
#include<stack>
#include<map>
#include<queue>
using namespace std;

int main()
{
    map<string,int> priority;
    string str;
    stack<string> op;
    queue<string> result;
    priority["("] = priority[")"] = 1;
    priority["+"] = priority["-"] = 2;
    priority["*"] = priority["/"] = 3;
    cin >> str;
    for(size_t i = 0;i != str.size();++i) {
    	string temp = "";
        if(((str[i] == '+' || str[i] == '-') && (!i || str[i - 1] == '(')) || isdigit(str[i])) {
            if(str[i] != '+')
            	temp += str[i];
            while(str[i + 1] == '.' || isdigit(str[i + 1]))
            	temp += str[++i];
            result.push(temp);
        } else {
            if(str[i] == '(') {
                op.push(temp + str[i]);
            }
            else if(str[i] == ')') {
                while(op.top() != "(") {
                	result.push(op.top());
                    op.pop();
                }
                op.pop();
            } 
            else {
                while(!op.empty() && priority[op.top()] >= priority[temp + str[i]]) {
                	result.push(op.top());
                    op.pop();
                }
                op.push(temp + str[i]);
            }
        }
    }
    while(!op.empty()) {
    	result.push(op.top());
        op.pop();
    }
    if(result.empty()) {
        return 0;
    } else {
    	cout << result.front();
    	result.pop();
    	while(!result.empty()) {
    		cout << " " << result.front();
    		result.pop();
    	}
    }
    return 0;
}   