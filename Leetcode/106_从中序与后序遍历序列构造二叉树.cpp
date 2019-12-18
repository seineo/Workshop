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
    TreeNode* help(vector<int>& inorder,vector<int>& postorder,int instart,int inend,int poststart,int postend) {
        if(instart > inend || poststart > postend) {
            return nullptr;
        }
        int root_data = postorder[postend];
        TreeNode* root = new TreeNode(root_data);
        int index = 0;
        while(inorder[instart + index] != root_data) {
            index++;
        }
        root->left = help(inorder,postorder,instart,instart + index - 1,poststart,poststart + index - 1);
        root->right = help(inorder,postorder,instart + index + 1,inend,poststart + index,postend - 1);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size() == 0 || postorder.size() == 0) {
            return nullptr;
        }
        return help(inorder,postorder,0,inorder.size() - 1,0,postorder.size() - 1);
    }
};