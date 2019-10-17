#include<iostream>
#include<cstring>
#include<array>
#include<numeric>
#include<functional>
#include<algorithm>
using namespace std;

template<typename T>
inline void PRINT_ELEMENTS(const T& coll, const string& optstr = "")
{
	cout << optstr;
	for (const auto& elem : coll) {
		cout << elem << " ";
	}
	cout << endl;
}

int main()
{
	// array<char,41> a;
	// strcpy(a.data(),"hello world");
	// printf("%s\n", a.data());

	array<int,4> a = {11,22,33,44};
	PRINT_ELEMENTS(a);

	a.back() = 9999999;
	a[a.size() - 2] = 42;
	PRINT_ELEMENTS(a);

	cout << "sum: " << accumulate(a.begin(),a.end(),0) << endl;

	transform(a.begin(),a.end(),a.begin(),negate<int>());
	PRINT_ELEMENTS(a);

	return 0;
}