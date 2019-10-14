#include<iostream>
#include<string>
#include<list>
#include<deque>
#include<vector>
#include<set>
#include<iterator>
#include<algorithm>
using namespace std;

int main()
{
	list<int> l;
	for (int i = 1; i <= 6; ++i) {
		l.push_front(i);
		l.push_back(i);
	}
	copy(l.cbegin(), l.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
	/*
	remove(l.begin(), l.end(), 3);
	
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
	cout << endl;*/  

	auto end = remove(l.begin(), l.end(), 3);
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "number of removed elements : " << distance(end, l.end()) << endl;
	
	l.erase(end, l.end());
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}