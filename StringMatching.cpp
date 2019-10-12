#include<iostream>
#include<string>
#include <cassert>

using namespace std;

int StringMatching(const string& str, const string& sub, size_t pos)
{
	assert(pos < str.size());
	size_t i = pos,j = 0;
	while(i != str.size() && j != sub.size()) {
		if(str[i] == sub[j]) {
			i++;	j++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}
	if(j == sub.size())
		return i - j;
	else
		return 0;
}

int main()
{
	string str = "aabbabc";
	string sub = "bc";
	cout << StringMatching(str,sub,0) << endl;
	return 0;
}