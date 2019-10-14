#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;

int main()
{
	// vector<string> v;
	// move(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(v));
	// sort(v.begin(), v.end());
	// unique_copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));

	vector<string> v{ istream_iterator<string>(cin),istream_iterator<string>() };
	sort(v.begin(), v.end());
	unique_copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
	return 0;
}