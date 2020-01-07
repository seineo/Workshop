#include<iostream>
#include<vector>

using namespace std;

using Tree = struct Node *;

struct Node {
    Node(int d) : data(d), left(nullptr), right(nullptr) {}

    int data;
    struct Node *left;
    struct Node *right;
};

bool flag = true;  //judge whether it's a BST
vector<int> post;

void post_tree(const vector<int> &pre, size_t low, size_t upper) {
    if (upper >= low) {
        int root = pre[low];
        size_t a = low + 1;
        size_t b = upper;
        if (flag) {    //for BST
            while (root > pre[a] && a <= b)
                a++;
            while (root <= pre[b] && b >= a)
                b--;
        } else {     //for mirror BST
            while (root <= pre[a] && a <= b)
                a++;
            while (root > pre[b] && b >= a)
                b--;
        }
        post_tree(pre, low + 1, b);   //deal with left tree
        post_tree(pre, a, upper);   //deal with right tree
        post.push_back(root);    //post order traverse
    }
}

int main() {
    size_t n;
    int num;
    vector<int> pre;
    cin >> n;
    for (size_t i = 0; i != n; ++i) {
        cin >> num;
        pre.push_back(num);
    }
    post_tree(pre, 0, n - 1);
    if (post.size() != n) {   //if it's a BST / mirror BST, the size of post should be n
        flag = false;
        post.clear();
        post_tree(pre, 0, n - 1);
    }
    if (post.size() == n) {
        cout << "YES" << endl;
        cout << post[0];
        for (size_t i = 1; i != n; ++i)
            cout << " " << post[i];
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
