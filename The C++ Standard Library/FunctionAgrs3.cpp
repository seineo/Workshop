#include<iostream>
#include<deque>
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
	deque<int> d{ 1,2,3,4,5 };
	PRINT_ELEMENTS(d, "initialized:    ");

	transform(d.cbegin(), d.cend(), d.begin(), negate<int>());
	PRINT_ELEMENTS(d, "negated:    ");

	transform(d.cbegin(), d.cend(), d.cbegin(), d.begin(), multiplies<int>());
	PRINT_ELEMENTS(d, "squared:    ");

	return 0;
}