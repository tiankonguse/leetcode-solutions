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
    vector<int> ans;
    void dfs(TreeNode* root){
        if(!root)return;
        ans.push_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }
public:
    vector<int> getAllElements(TreeNode* r1, TreeNode* r2) {
        dfs(r1);
        dfs(r2);
        sort(ans.begin(), ans.end());
        return ans;
    }
};


