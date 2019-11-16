#include<iostream>
#include<stack>
#include<queue>
#include<assert.h>
using namespace std;

struct Car {
	Car(int n, int t) :number(n), time(t) {}

	size_t number;
	size_t time;
};

int main()
{
	stack<Car> parking_lot, temp;
	queue<Car> path;
	char state;
	size_t capacity, num, t;
	cin >> capacity;  
	while (cin >> state >> num >> t) {
		assert(num >= 0 && t >= 0);
		switch (state) {
		case 'A':
			if (parking_lot.size() != capacity) {
				parking_lot.push(Car(num, t));
				cout << "In parking lot : " << parking_lot.size() << endl;   //位置从1计数
			} else {
				path.push(Car(num, t));
				cout << "On path : " << path.size() << endl;
			}
			break;
		case 'D':
			while (!parking_lot.empty() && parking_lot.top().number != num) {
				temp.push(parking_lot.top());
				parking_lot.pop();
			}
			if (parking_lot.empty()) {
				cerr << "No car found(May be on path)" << endl;
				exit(1);
			} else {
				size_t time = parking_lot.top().time;
				parking_lot.pop();
				while (!temp.empty()) {
					parking_lot.push(temp.top());
					temp.pop();
				}
				if (!path.empty()) {
					Car in = path.front();
					in.time = t;       //因为在便道的时间不收费，所以更新离开便道的时间
					parking_lot.push(in);
					path.pop();
				}
				cout << "Time : " << t - time << " fare : " << 2 * (t - time) << endl;
			}                             //假定费用为停留时间的两倍 
			break;
		case 'E':
			cout << "End" << endl;
			exit(0);
		default:
			cerr << "State error" << endl;
			exit(1);
		}
	}
	return 0;
}