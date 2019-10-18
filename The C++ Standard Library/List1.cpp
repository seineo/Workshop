#include<iostream>
#include<list>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

void PrintLists(const list<int>& l1, const list<int>& l2)
{
	cout << "list1: ";
	copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
	cout << "list2: ";
	copy(l2.begin(), l2.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main()
{
	list<int> l1, l2;
	for (int i = 0; i != 6; ++i) {
		l1.push_back(i);
		l2.push_front(i);
	}
	PrintLists(l1, l2);

	l2.splice(find(l2.begin(), l2.end(), 3), l1);
	PrintLists(l1, l2);

	l2.splice(l2.end(), l2, l2.begin());
	PrintLists(l1, l2);

	l2.sort();
	l1 = l2;
	l2.unique();
	PrintLists(l1, l2);

	l1.merge(l2);
	PrintLists(l1, l2);
	return 0;
}