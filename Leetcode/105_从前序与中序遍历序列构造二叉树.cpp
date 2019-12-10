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
    TreeNode* helper(vector<int>& preorder, vector<int>& inorder,int in_start,int in_end,int pre_start,int pre_end) {
        if(pre_start > pre_end || in_start > in_end) {
            return nullptr;
        }
        int root_data = preorder[pre_start];
        TreeNode* root = new TreeNode(root_data);
        int index = 0;
        while(inorder[in_start + index] != root_data) {
            index++;
        }
        root->left = helper(preorder,inorder,in_start,in_start + index - 1,pre_start + 1,pre_start + index);
        root->right = helper(preorder,inorder,in_start + index + 1,in_end,pre_start + index + 1,pre_end);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0 || inorder.size() == 0) {
            return nullptr;
        }
        return helper(preorder,inorder,0,inorder.size() - 1,0,preorder.size() - 1);
    }
};