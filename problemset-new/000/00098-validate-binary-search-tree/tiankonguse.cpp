/*************************************************************************
    > File Name: tiankonguse.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu May 16 23:49:15 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

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
    bool dfs(TreeNode* root, int& minVal, int& maxVal){
        if(!root){
            return true;
        }

        minVal = maxVal = root->val;
        if(root->left){
            int leftMinVal = -1, leftMaxVal = -1;
            if(!dfs(root->left, leftMinVal, leftMaxVal)){
                return false;
            }
            if(leftMaxVal >= root->val){
                return false;
            }
            minVal = leftMinVal;
        }
        if(root->right){
            int rightMinVal = -1, rightMaxVal = -1;
            if(!dfs(root->right, rightMinVal, rightMaxVal)){
                return false;
            }
            if(rightMinVal <= root->val){
                return false;
            }
            maxVal = rightMaxVal;
        }
        return true;
    }
public:
    bool isValidBST(TreeNode* root, int minVal = -1, int maxVal = -1) {
         return dfs(root, minVal, maxVal);
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
    #define CLASS Solution
    #define FUNCTION isValidBST

    TreeNode* first;
    bool expectAns;

    first = vecToTree({2,1,3});
    expectAns = true;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = vecToTree({5,1,4,null,null,3,6});
    expectAns = false;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);


    return 0;
}
