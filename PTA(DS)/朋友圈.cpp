#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> pre;
vector<int> num;

int union_find(int x)
{
	int root = x;
	while(root != pre[root])  //寻找根节点
		root = pre[root];
	int son = x,temp;
	while(son != root) {     //路径压缩
		temp = pre[son];
		pre[son] = root;
		son = temp;
	}
	return root;
}

void join(int x,int y)
{
	int root1 = union_find(x);
	int root2 = union_find(y);
	if(root1 != root2) {
		pre[root2] = root1;   //以root1为根节点
		num[root1] += num[root2];
	}
}

int main()
{
	int n,m,per_num,a,b;
	cin >> n >> m;
	pre.resize(n + 1);
	for(int i = 0;i <= n;++i)
		pre[i] = i;
	num.resize(n + 1,1);
	while(m--) {
		cin >> per_num;
		cin >> a;
		while(--per_num) {
			cin >> b;
			join(a,b);
		}
	}
	cout << *max_element(num.begin(),num.end()) << endl;
	return 0;
}