/*************************************************************************
    > File Name: 95-tiankonguse.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: Sun Jun 16 22:46:20 2019
 ************************************************************************/

class Solution {
public:
    vector<TreeNode*> generateTrees(int n, int start = 1) {
        vector<TreeNode*> ans;
        if(n <= 0){
            return ans;
        }
        if(n == 1){
            ans.push_back(new TreeNode(start));
            return ans;
        }
        vector<TreeNode*> left, right;
        for(int i = start; i < start+n; i++){
            left = generateTrees(i-start, start);
            right = generateTrees(start+n - i - 1, i + 1);
            
            if(left.size() == 0){
                left.push_back(NULL);
            }
            if(right.size() == 0){
                right.push_back(NULL);
            }
            
            for(auto leftNode: left){
                for(auto rightNode: right){
                    TreeNode* root = new TreeNode(i);
                    root->left = leftNode;
                    root->right = rightNode;
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
};


