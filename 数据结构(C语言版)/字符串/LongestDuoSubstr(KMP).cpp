#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> next_pos;

void GetNext(const string& s)
{
	int len = s.size();
	int k = -1;
	int j = 0;
	next_pos.resize(len);
	next_pos[0] = -1;
	while(j != len - 1) {
		if(k == -1 || s[j] == s[k]) {
			++j;
			++k;
			if(s[j] != s[k])
				next_pos[j] = k;
			else
				next_pos[j] = next_pos[k];
		}
		else
			k = next_pos[k];
	}
}

int KMPMatching(const string& source, const string& target) 
{
	int i = 0,j = 0;
	int s_len = source.size(),t_len = target.size();
	GetNext(target);
	while(i != s_len && j != t_len) {
		if(j == -1 || source[i] == target[j]) {
			++i;
			++j;
		} else {
			j = next_pos[j];
		}
	}
	if(j == t_len)
		return i - j;
	else 
		return -1;
}

void LongestDupSubstr(const string& s)
{
	size_t pos;
	string s1,s2;
	for(size_t len = s.size() / 2;len != 0;len--) {
		for(size_t i = 0;i != s.size() - len;++i) {
			s1 = s.substr(i,len);
			s2 = s.substr(i + len);
			if(KMPMatching(s2,s1) != -1) {    //当然也可以用s2.find(s1) != string::npos
				cout << s1 << endl;
				return;
			}
		}
	}
	cout << "Not found" << endl;
}

int main()
{
	string str;
	cin >> str;
	LongestDupSubstr(str);
	return 0;
}