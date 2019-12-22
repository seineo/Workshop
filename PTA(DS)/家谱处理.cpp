#include<iostream>
#include<unordered_map>
#include<string>
#include<array>
using namespace std;

int main()
{
	int n,m;
	unordered_map<string,string> f;   //存储名字及其parent的名字
	array<string,110> name_list;   //名字表
	string name,relation;
	cin >> n >> m;
	cin.get();
	while(n--) {
		getline(cin,name);
		int count = 0;
		while(name[count] == ' ') 
			count++;
		name = name.substr(count);   //删除空格
		if(count == 0) {  //最早祖先
			f[name] = "root";
			name_list[count] = name;   //将名字存入名字表
		} else {
			f[name] = name_list[count / 2 - 1];
			name_list[count / 2] = name;
		}
	}
	string a,b,c,d;
	while(m--) {
		cin >> a >> d >> d >> b >> d >> c;
		switch(b[0]) {
			case 'c':
				cout << (f[a] == c ? "True" : "False") << endl;	break;
			case 'p':
				cout << (f[c] == a ? "True" : "False") << endl;	break;
			case 's':
				cout << (f[a] == f[c] ? "True" : "False") << endl;	break;
			case 'd':
				while(f[a] != c && f[a] != "root")
					a = f[a];
				cout << (f[a] == c ? "True" : "False") << endl;	break;
			case 'a':
				while(f[c] != a && f[c] != "root")
					c = f[c];
				cout << (f[c] == a ? "True" : "False") << endl;	break;
		}
	}
	return 0;
}