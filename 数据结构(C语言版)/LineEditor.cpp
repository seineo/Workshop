/*
Type in '#' —— backspace.
Type in '@' —— delete the whole line.
*/

#include<iostream>
#include<string>
#include <stack>
#include <fstream>
#include<algorithm>
using namespace std;

void LineEdit()
{
	ofstream out("test.txt",ios::out); 
	stack<char> s;
	string str;
	char c;
	while ((c = cin.get()) != EOF) {
		if (c != '\n') {
			switch (c) {
			case '#': s.pop();	break;
			case '@': stack<char>().swap(s);	break;
			default: s.push(c);	break;
			}
		}
		else {   //'\n'
			while (!s.empty()) {
				str += s.top();
				s.pop();
			}
			reverse(str.begin(), str.end());
			out << str;
			out << '\n';
			str.clear();
		}
	}
}

int main()
{
	LineEdit();
	return 0;
}

//input :
//whli##ilr#e(s#*s)
//    outchar@putchar(*s=#++);

//output in file :
//while(*s)
//putchar(*s++);
