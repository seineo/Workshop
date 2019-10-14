#include<iostream>
#include<string>
#include<deque>
#include<algorithm>
using namespace std;

bool pred(int i)
{
	return i > 5 && i < 12;
}

class Pred {
public:
	Pred(int xx, int yy) :x(xx), y(yy) {}
	bool operator()(int i) { return i > x&&i < y; }
private:
	int x;
	int y;
};

int main()
{
	deque<int> d{ 1,3,19,5,13,7,11,2,17 };
	int x = 5;
	int y = 12;

	// deque<int>::const_iterator pos;
	// pos = find_if(d.cbegin(), d.cend(), Pred(x, y));
	// cout << *pos << endl;

	/*deque<int>::const_iterator i;
	for (i = d.begin(); i != d.end(); ++i) {
		if (*i > x &&*i < y)
			break;
	}
	cout << *i << endl;*/

	/*deque<int>::const_iterator pos;
	pos = find_if(d.cbegin(), d.cend(), pred);
	cout << *pos << endl;*/
	
	auto pos = find_if(d.cbegin(), d.cend(),
		[=](int i) {return i > x && i < y; });
	cout << *pos << endl;
	return 0;
}