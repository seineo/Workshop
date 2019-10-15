#include<iostream>
#include<string>
#include<vector>
#include<list>
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

class AddValue {
private:
	int theValue;
public:
	AddValue(int v) :theValue(v) {}
	void operator()(int& elem) const {
		elem += theValue;
	}
};

int main()
{
	list<int> l;
	for (int i = 1; i <= 9; ++i) {
		l.push_back(i);
	}
	PRINT_ELEMENTS(l, "initialized:    ");

	for_each(l.begin(), l.end(), AddValue(10));
	PRINT_ELEMENTS(l, "after adding 10:    ");

	for_each(l.begin(), l.end(), AddValue(*l.begin()));
	PRINT_ELEMENTS(l, "after adding first element:    ");

	system("pause");
}