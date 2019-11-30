#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

using Tree = int;

struct Elem {
    Elem(char d,Tree l,Tree r):data(d),left(l),right(r){}
    char data;
    Tree left;
    Tree right;
};

vector<Elem> t1,t2;

Tree CreateTree(vector<Elem>& t,int n)   //将树用vector储存，左右子树用下标
{
    if(n == 0)
        return -1;
    char data,l,r;
    Tree left,right;
    vector<int> flag(n);   //根不为任何结点的孩子 判断是否为根的flag 
    while(n--) {
        cin >> data >> l >> r;
        if(l != '-') {
            left = l - '0';
            flag[left] = 1;
        } else {
            left = -1;
        }
        if(r != '-') {
            right = r - '0';
            flag[right] = 1;
        } else {
            right = -1;
        }
        t.push_back(Elem(data,left,right));
    }
    auto pos = find_if(flag.begin(),flag.end(),[](int i){return i == 0;});
    return distance(flag.begin(),pos);  //根节点
}

bool Isomorphic(Tree tree1,Tree tree2) 
{
    if((tree1 == -1) ^ (tree2 == -1))
        return false;
    if(tree1 == -1 && tree2 == -1)
        return true;
    if(t1[tree1].data == t2[tree2].data) {
        if(Isomorphic(t1[tree1].left,t2[tree2].left) && Isomorphic(t1[tree1].right,t2[tree2].right))
            return true;
        if(Isomorphic(t1[tree1].left,t2[tree2].right) && Isomorphic(t1[tree1].right,t2[tree2].left))
            return true;
    }
    return false;
}

int main()
{
    Tree root1,root2;
    int n;
    cin >> n;
    root1 = CreateTree(t1,n);
    cin >> n;
    root2 = CreateTree(t2,n);
    if(Isomorphic(root1,root2)) 
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}