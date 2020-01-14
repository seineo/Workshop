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
    void flatten(TreeNode* root) {
         if(root != nullptr) {
            flatten(root->left);
            flatten(root->right);
            if(root->left != nullptr) {
                TreeNode* temp = root->left;
                while(temp->right != nullptr) {
                    temp = temp->right;
                }
                temp->right = root->right;
                root->right = root->left;
                root->left = nullptr;
            }
        }
    }
};
