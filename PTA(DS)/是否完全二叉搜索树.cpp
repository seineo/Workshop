// 将一系列给定数字顺序插入一个初始为空的二叉搜索树（定义为左子树键值大，右子树键值小），你需要判断最后的树是否一棵完全二叉树，并且给出其层序遍历的结果。

// 输入格式：
// 输入第一行给出一个不超过20的正整数N；第二行给出N个互不相同的正整数，其间以空格分隔。

// 输出格式：
// 将输入的N个正整数顺序插入一个初始为空的二叉搜索树。在第一行中输出结果树的层序遍历结果，数字间以1个空格分隔，行的首尾不得有多余空格。第二行输出YES，如果该树是完全二叉树；否则输出NO。

// 输入样例1：
// 9
// 38 45 42 24 58 30 67 12 51
// 输出样例1：
// 38 45 24 58 42 30 12 67 51
// YES
// 输入样例2：
// 8
// 38 24 12 45 58 67 42 51
// 输出样例2：
// 38 45 24 58 42 12 67 51
// NO

#include<iostream>
#include<queue>
using namespace std;

using Tree = struct TNode*;

struct TNode {
	TNode(int d):data(d),left(nullptr),right(nullptr){}
	int data;
	struct TNode* left;
	struct TNode* right;
};

Tree Insert(Tree t,int x)
{
	if(t == nullptr) 
		t = new TNode(x);
	else if(x > t->data)
		t->left = Insert(t->left,x);
	else
		t->right = Insert(t->right,x);
	return t;
}

bool Judge(Tree t)
{
	queue<Tree> q;
	q.push(t);
	Tree temp;
	while((temp = q.front()) != nullptr) {
		q.pop();
		q.push(temp->left);
		q.push(temp->right);
	}
	while(!q.empty()) {
		temp = q.front();
		q.pop();
		if(temp != nullptr){
			return false;
		}
	}
	return true;
}

void LevelTraverse(Tree t)
{
	if(t == nullptr)
		return;
	queue<Tree> q;
	q.push(t);
	Tree temp;
	bool first = true;
	while(!q.empty()) {
		temp = q.front();
		q.pop();
		if(first) {
			printf("%d",temp->data);
			first = false;
		} else {
			printf(" %d",temp->data);
		}
		if(temp->left != nullptr)
			q.push(temp->left);
		if(temp->right != nullptr) 
			q.push(temp->right);
	}
}

int main()
{
	int n,num;
	Tree t = nullptr;
	cin >> n;
	while(n--) {
		cin >> num;
		t = Insert(t,num);
	}
	LevelTraverse(t);
	printf("\n");
	if(Judge(t)) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
	return 0;
}