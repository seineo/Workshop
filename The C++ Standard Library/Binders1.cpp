#include<iostream>
#include<string>
#include<deque>
#include<set>
#include<iterator>
#include<functional>
#include<algorithm>
using namespace std;
using namespace std::placeholders;

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
	set<int, greater<int>> s = { 1,2,3,4,5,6,7,8,9 };
	deque<int> d;

	PRINT_ELEMENTS(s, "initialized:    ");

	transform(s.cbegin(), s.cend(), back_inserter(d), bind(multiplies<int>(),_1, 10));
	PRINT_ELEMENTS(d, "transformed:    ");

	replace_if(d.begin(), d.end(), bind(equal_to<int>(), _1, 70), 42);
	PRINT_ELEMENTS(d, "replaced:    ");

	d.erase(remove_if(d.begin(), d.end(),bind(logical_and<int>(), 
		bind(greater_equal<int>(), _1, 50), bind(less_equal<int>(), _1, 80))), d.end());
	PRINT_ELEMENTS(d, "removed:    ");

	return 0;
}