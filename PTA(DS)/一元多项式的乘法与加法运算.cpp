#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

struct Node {
	friend ostream& operator<<(ostream&,const Node&);
	Node(int c,int e):coef(c),expo(e){}

	int coef;
	int expo;
};

ostream& operator<<(ostream& os,const Node& n)
{
	os << n.coef << " " << n.expo;
	return os;
}

list<Node> Add(const list<Node>& l1, const list<Node>& l2)
{
	list<Node> sum;
	auto cur1 = l1.begin(),cur2 = l2.begin();
	while(cur1 != l1.end() && cur2 != l2.end()) {
		if(cur1->expo > cur2->expo) {
			sum.push_back(Node(cur1->coef,cur1->expo));
			cur1++;
		}
		else if(cur1->expo < cur2->expo) {
			sum.push_back(Node(cur2->coef,cur2->expo));
			cur2++;
		}
		else {
			int coef_sum = cur1->coef + cur2->coef;
			if(coef_sum != 0) {
				sum.push_back(Node(coef_sum,cur1->expo));
			}
			cur1++;cur2++;
		}
	}
	for_each(cur1,l1.end(),[&](const Node& n){sum.push_back(Node(n.coef,n.expo));});
	for_each(cur2,l2.end(),[&](const Node& n){sum.push_back(Node(n.coef,n.expo));});
	return sum;
}

list<Node> Multiple(const list<Node>& l1, const list<Node>& l2)
{
	list<Node> product;
	for(const auto& i : l1) {
		list<Node> temp;
		for(const auto& j : l2) {
			temp.push_back(Node(i.coef * j.coef,i.expo + j.expo));
		}
		product = Add(temp,product);
	}
	return product;
}

int main()
{
	list<Node> l1,l2,sum,product;
	int total;
	int coef,expo;
	cin >> total;
	while(total--) {
		cin >> coef >> expo;
		l1.push_back(Node(coef,expo));
	}
	cin >> total;
	while(total--) {
		cin >> coef >> expo;
		l2.push_back(Node(coef,expo));
	}
	product = Multiple(l1,l2);
	if(product.empty()) {
		cout << "0 0" << endl;
	} else {
		bool first = true;
		for(const auto& i : product) {
			if(first) {
				cout << i;
				first = false;
			} else {
				cout << " " << i;
			}
		}
		cout << endl;
	}
	sum = Add(l1,l2);;
	if(sum.empty()) {
		cout << "0 0" << endl;
	} else {
		bool first = true;
		for(const auto& i : sum) {
			if(first) {
				cout << i;
				first = false;
			} else {
				cout << " " << i;
			}
		}
		cout << endl;
	}
	return 0;
}	