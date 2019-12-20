#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;

int main()
{
	stack<int> s1,s2;    //令s1为输入栈，s2为输出栈
	int n1,n2,item;
	char op;
	cin >> n1 >> n2;
	int Min = min(n1,n2);
	while(cin >> op && op != 'T') {
		if(op == 'A') {
			cin >> item;
			if(s1.size() < Min) {
					s1.push(item);
			} else {
				if(s2.empty()) {
					while(!s1.empty()) {
						s2.push(s1.top());
						s1.pop();
					}
					s1.push(item);
				} else {
					cout << "ERROR:Full" << endl;
				}
			}
		} else {
			if(s2.empty()) {
				if(s1.empty()) {
					cout << "ERROR:Empty" << endl;
				} else {
					while(!s1.empty()) {
						s2.push(s1.top());
						s1.pop();
					}
					cout << s2.top() << endl;
					s2.pop();
				}
			} else {
				cout << s2.top() << endl;
				s2.pop();
			}
		}
	}
	return 0;
}