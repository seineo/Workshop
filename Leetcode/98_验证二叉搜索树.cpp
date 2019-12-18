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
    bool helper(TreeNode* root, long lower, long upper) {
        if(root == NULL ) {
            return true;
        }
        if(root->val <= lower) {
            return false;
        }
        if(root->val >= upper) {
            return false;
        }
        if(!helper(root->left,lower,root->val)){
            return false;
        }
        if(!helper(root->right,root->val,upper)) {
            return false;
        }
        return true;
    }
    bool isValidBST(TreeNode* root) {
        return helper(root,LONG_MIN,LONG_MAX);
    }
    
    // bool isValidBST(TreeNode* root) {   //中序遍历出来的树就应该满足二叉搜索树
    //     if(root == NULL) {
    //         return true;
    //     }
    //     stack<TreeNode*> s;
    //     int small = INT_MIN;
    //     bool init = true;     //记录是否是第一次的标志 第一次的话对于无左子树且根节点值就等于small的树是不应该返回false的
    //     while(root != NULL || !s.empty()) {
    //         while(root != NULL) {
    //             s.push(root);
    //             root = root->left;
    //         }
    //         root = s.top();
    //         s.pop();
    //         if(!init && root->val <= small) {
    //             return false;
    //         }
    //         init = false;
    //         small = root->val;
    //         root = root->right;
    //     }
    //     return true;
    // }
};