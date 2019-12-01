#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

using Tree = struct TNode*;

struct TNode {
    TNode(int d):data(d),left(nullptr),right(nullptr){}

    int data;
    Tree left;
    Tree right;
};

Tree Insert(Tree t,int data)
{
    if(t == nullptr)
        t = new TNode(data);
    else if(data < t->data)
        t->left = Insert(t->left,data);
    else if(data > t->data)
        t->right = Insert(t->right,data);
    return t;
}

Tree CreateTree(int elem_num)
{
    Tree root = nullptr;
    int data;
    for(int i = 0;i != elem_num;++i) {
        cin >> data;
        root = Insert(root,data);
    }
    return root;
}

bool Compare(Tree origin,Tree to_comp)
{
    if((origin == nullptr) ^ (to_comp == nullptr)) 
        return false;
    if(origin == nullptr)
        return true;
    if(origin->data == to_comp->data) {
        if(Compare(origin->left,to_comp->left) && Compare(origin->right,to_comp->right))
            return true;
    }
    return false;
}

void JudgeSameBST()
{
    int elem_num,seq_num;
    while(cin >> elem_num && elem_num != 0) {
        cin >>seq_num;
        Tree origin = CreateTree(elem_num);
        while(seq_num--) {
            Tree to_comp = CreateTree(elem_num);
            if(Compare(origin,to_comp)) 
                cout << "Yes" << endl;
            else 
                cout << "No" << endl;
        }
    }
}

int main()
{
    JudgeSameBST();
    return 0;
}