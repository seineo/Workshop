// 请编写程序检查C语言源程序中下列符号是否配对：/*与*/、(与)、[与]、{与}。

// 输入格式:
// 输入为一个C语言源程序。当读到某一行中只有一个句点.和一个回车的时候，标志着输入结束。程序中需要检查配对的符号不超过100个。

// 输出格式:
// 首先，如果所有符号配对正确，则在第一行中输出YES，否则输出NO。然后在第二行中指出第一个不配对的符号：如果缺少左符号，则输出?-右符号；如果缺少右符号，则输出左符号-?。

// 输入样例1：
// void test()
// {
//     int i, A[10];
//     for (i=0; i<10; i++) /*/
//         A[i] = i;
// }
// .

// 输出样例1：
// NO
// /*-?
// 输入样例2：
// void test()
// {
//     int i, A[10];
//     for (i=0; i<10; i++) /**/
//         A[i] = i;
// }]
// .

// 输出样例2：
// NO
// ?-]
// 输入样例3：
// void test()
// {
//     int i
//     double A[10];
//     for (i=0; i<10; i++) /**/
//         A[i] = 0.1*i;
// }
// .

// 输出样例3：
// YES


#include<iostream>
#include<stack>
#include<string>
#include<map>
using namespace std;

string error;

bool Judge()
{
	string str;
	stack<char> s;
	while(getline(cin,str) && str != "." && str != "\n") {
		size_t len = str.size();
		for(size_t i = 0;i != len;++i) {
			switch(str[i]) {
				case '(':	case '[':	
				case '{':	
					s.push(str[i]);	break;
				case ')':	
					if(!s.empty() && s.top() == '(')
						s.pop();
					else {
						if(s.empty()) 
							error = ")";
						else
							error.push_back(s.top());
						return false;
					}
					break;
				case ']':
					if(!s.empty() && s.top() == '[')
						s.pop();
					else {
						if(s.empty()) 
							error = "]";
						else
							error.push_back(s.top());
						return false;
					}
					break;
				case '}':
					if(!s.empty() && s.top() == '{')
						s.pop();
					else {
						if(s.empty()) 
							error = "}";
						else
							error.push_back(s.top());
						return false;
					}
					break;
				case '/':
					if(str[i + 1] == '*') {
						s.push(str[i]);
						i++;
					}
					break;
				case '*':
					if(str[i + 1] == '/') {
						if(!s.empty() && s.top() == '/') {
							s.pop();
							i++;
						} else {
							if(s.empty()) 
								error = "*/";
							else
								error.push_back(s.top());
							return false;
						}
					}
					break;
			}
		}
	}
	if(!s.empty())
		error = s.top();
	return s.empty();
}

int main()
{
	if(Judge()) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;	
		if(error == "(" || error == "[" || error == "{" || error == "/") {
			if(error == "/")
				cout << "/*-?" << endl;
			else
				cout << error << "-?" << endl;
		} else {
			cout << "?-" << error << endl;
		}
	}
	return 0;
}