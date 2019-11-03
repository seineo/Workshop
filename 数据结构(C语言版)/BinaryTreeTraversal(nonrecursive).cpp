#include<iostream>
#include<cstdlib>
#include<stack>
#include<deque>
#include<algorithm>
using namespace std;

#define ElemType int

typedef struct TreeNode {
	ElemType data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode,*Tree;

void CreateBinaryTree(Tree& t)
{
	ElemType elem;
	cin >> elem;
	if(elem == -1)
		t = nullptr;
	else {
		t = (Tree)malloc(sizeof(TreeNode));
		if(!t)	exit(-1);
		t->data = elem;
		CreateBinaryTree(t->left);
		CreateBinaryTree(t->right);
	}
}

void PreorderTraversal(Tree t)
{
	stack<Tree> path;
	Tree cur = t;
	while(cur != nullptr || !path.empty()) {
		while(cur != nullptr) {
			path.push(cur);
			cout << cur->data << " ";
			cur = cur->left;
		}
		cur = path.top();
		path.pop();
		cur = cur->right;
	}
}

void InorderTraversal(Tree t)   
{
	stack<Tree> path;
	Tree cur = t;
	while(cur != nullptr || !path.empty()) {
		while(cur != nullptr) {
			path.push(cur);
			cur = cur->left;
		}
		cur = path.top();
		cout << cur->data << " ";
		path.pop();
		cur = cur->right;
	}
}

void PostorderTraversal(Tree t)
{
	deque<ElemType> d;
	stack<Tree> path;
	Tree temp;
	path.push(t);
	while(!path.empty()) {
		temp = path.top();
		d.push_front(temp->data);
		path.pop();
		if(temp->left)
			path.push(temp->left);
		if(temp->right)
			path.push(temp->right);
	}
	for(const auto& i : d)
		cout << i << " ";
}

int main()
{
	Tree t;
	CreateBinaryTree(t);
	PreorderTraversal(t);
	cout << endl;
	InorderTraversal(t);
	cout << endl;
	PostorderTraversal(t);
	cout << endl;
	return 0;
}