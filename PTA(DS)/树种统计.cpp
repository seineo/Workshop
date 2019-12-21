#include<iostream>
#include<map>
#include<string>
#include<iomanip>
using namespace std;

int main()
{
	size_t n;
	string str;
	map<string,size_t> m;
	cin >> n;
	cin.get();
	for(size_t i = 0;i != n;++i) {
		getline(cin,str);
		m[str]++;
	}
	for(const auto& i : m) {
		cout << i.first << " " << fixed << setprecision(4)
		 << static_cast<float>(i.second) * 100 / n << "%" << endl;
	}
	return 0;
}