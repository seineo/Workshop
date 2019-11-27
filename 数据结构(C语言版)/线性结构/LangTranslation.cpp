#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
	string str;
	stack<char> s;
	queue<char> q;
	cin >> str;
	for_each(str.rbegin(),str.rend(),[&](const char& ch){s.push(ch);});
	while(!s.empty()) {
		char ch = s.top();
		s.pop();
		if(ch == 'B') {
			string trans = "tAdA";
			for_each(trans.rbegin(),trans.rend(),[&](const char& ch){s.push(ch);});
		}
		else if(ch == 'A') {
			cout << "sae";
		}
		else if(ch == '(') {
			while(s.top() != ')') {
				q.push(s.top());
				s.pop();
			}
			s.pop();
			char front = q.front();
			q.pop();
			string trans;
			while(!q.empty()) {
				trans.append({front,q.front()});
				q.pop();
			}
			trans.push_back(front);
			for_each(trans.begin(),trans.end(),[&](const char& ch){s.push(ch);});
		}
		else {
			cout << ch;
		}
	}
	return 0;
}
