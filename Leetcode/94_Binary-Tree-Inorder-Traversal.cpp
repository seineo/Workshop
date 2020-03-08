/*
 *  problem: https://leetcode-cn.com/problems/binary-tree-inorder-traversal/
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//Solution 1 (Recursion):
//Time complexity: O(n)
//Space complexity: O(n)

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> tree;
        helper(root,tree);
        return tree;
    }

    void helper(TreeNode* root, vector<int>& tree) {
        if(root != nullptr) {
            helper(root->left,tree);
            tree.push_back(root->val);
            helper(root->right,tree);
        }
    }
};

//Solution 2 (Iteration):
//Time complexity: O(n)
//Space complexity: O(n)

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> v;
        TreeNode* cur = root;
        while(cur != nullptr || !s.empty()) {
            while(cur != nullptr) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            v.push_back(cur->val);
            cur = cur->right;
        }
        return v;
    }
};
