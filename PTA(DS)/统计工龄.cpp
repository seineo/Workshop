#include<iostream>
#include<map>
using namespace std;

int main()
{
	map<int,int> m;
	int num,age;
	cin >> num;
	while(num--) {
		cin >> age;
		m[age]++;
	}
	for(const auto& i : m) {
		cout << i.first << ":" << i.second << endl;
	}
	return 0;
}
