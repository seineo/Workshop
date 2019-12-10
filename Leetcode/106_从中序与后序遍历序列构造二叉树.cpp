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
    TreeNode* help(vector<int>& inorder,vector<int>& postorder,int left_length) {

    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size() == 0 || postorder.size() == 0) {
            return nullptr;
        }
        int root_data = postorder[postorder.size() - 1];
        auto loc = find(inorder.begin(),inorder.end(),root_data);
        
    }
};