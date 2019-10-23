#include<iostream>
#include <stack>
#include<queue>
#include<string>
using namespace std;

int main()
{
	stack<char> s;
	queue<char> temp;
	string str;
	char front;
	cin >> str;
	for (auto i = str.rbegin(); i != str.rend(); ++i) {
		s.push(*i);
	}
	while (!s.empty()) {
		char top = s.top();
		if (top == 'A') {
			s.pop();
			cout << "sae";
		}
		else if (top == 'B') {
			s.pop();
			string result = "tAdA";
			for (auto i = result.rbegin(); i != result.rend(); ++i) {
				s.push(*i);
			}
		}
		else if (top == '(') {
			s.pop();
			front = s.top();
			while (s.top() != ')') {
				temp.push(s.top());
				s.pop();
			}
			s.pop();
			string result;
			temp.pop();
			while (!temp.empty()) {
				result.append({ front,temp.front() });
				temp.pop();
			}
			result.push_back(front);
			for (const auto& i : result)
				s.push(i);
		}
		else {
			cout << s.top();
			s.pop();
		}
	}
	return 0;
}