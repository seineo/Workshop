/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int> cur;
        vector<vector<int>> total;
        if(root == nullptr) {
            return total;
        }
        AddPath(root,sum,cur,total);
        return total;
    }
    void AddPath(TreeNode* root,int sum,vector<int>& cur,vector<vector<int>>& total) {
        sum -= root->val;
        cur.push_back(root->val);
        if(sum == 0 && root->left == nullptr && root->right == nullptr) {
            total.push_back(cur);
            return;
        }
        if(root->left) {
            AddPath(root->left,sum,cur,total);
            cur.pop_back();
        }
        if(root->right) {
            AddPath(root->right,sum,cur,total);
            cur.pop_back();
        }
    }
};