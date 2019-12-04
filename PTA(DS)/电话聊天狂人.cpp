#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
	int num;
	map<string,int> m;
	string out,in;
	cin >> num;
	while(num--) {
		cin >> out >> in;
		m[out]++;
		m[in]++;
	}
	string result;
	int max = -1,count = 0;
	for(const auto& i : m) {
		if(i.second > max) {
			max = i.second;
			result = i.first;
		}
	}
	for_each(m.begin(),m.end(),[&](decltype(m)::value_type i){if(i.second == max) count++;});
	if(count == 1) {
		cout << result << " " << max << endl;
	} else {
		cout << result << " " << max << " " << count << endl;
	}
	return 0;
}
