#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	string str;
	cin >> n;
	while(n--) {
		bool flag = false;
		cin >> str;
		for(size_t i = 1;i <= str.size() / 2;++i) {
			if(str.size() % i == 0) {
				string temp = str.substr(0,i);
				string to_comp;
				for(size_t j = 0;j != str.size() / i;++j) {
					to_comp.append(temp);
				}
				if(str == to_comp) {
					cout << i << endl;
					flag = true;
					break;
				}
			}
		}
		if(!flag) {
			cout << str.size() << endl;
		}
	}
	return 0;
}