#include<iostream>
#include<stack>
#include<vector>
using namespace std;

bool Judge(const vector<int>& v,int m,int n)
{
	stack<int> s;
	int top = 0,size = 0;
	for(int i = 0;i != n;++i) {
		if(v[i] > top) {
			if(v[i] - top + size > m)
				return false;
			for(int j = top + 1;j <= v[i];++j) {
				s.push(j);
				size++;
			}
			top = v[i];
			s.pop();
			size--;
		} else { 
			if(!s.empty() && s.top() == v[i]) {
				s.pop();
				size--;
			}
			else 
				return false;
		}
	}
	return s.empty();
}

int main()
{
	int m,n,k,num;
	cin >> m >> n >> k;
	while(k--) {
		vector<int> v; 
		for(int i = 0;i != n;++i) {
			cin >> num;
			v.push_back(num);
		}
		if(Judge(v,m,n)) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}