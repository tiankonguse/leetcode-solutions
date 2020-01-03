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
    int maxDep, maxSUm;
public:
    int deepestLeavesSum(TreeNode* r, int lev = -1) {
        if(lev == -1){ //init 
            maxDep = -1, maxSUm = 0;
        }
        if(!r){ //empty 
            
        }else if(!r->left && !r->right){ //leaves
            if(lev == maxDep){ //add 
                maxSUm += r->val; 
            }else if(lev > maxDep){ //reset
                maxDep = lev;
                maxSUm = r->val;
            }
        }else{
            deepestLeavesSum(r->left, lev+1);
            deepestLeavesSum(r->right, lev+1);
        }
        
        return maxSUm;
    }
};
