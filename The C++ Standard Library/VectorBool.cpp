#include<iostream>
#include<vector>
#include<string>
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
	vector<bool> v{ 1,0,1, };
	PRINT_ELEMENTS(v);
	v.flip();
	PRINT_ELEMENTS(v);
	v[1].flip();
	PRINT_ELEMENTS(v);
	v[0] = 1;
	v[2] = v[0];
	PRINT_ELEMENTS(v);
	return 0;
}