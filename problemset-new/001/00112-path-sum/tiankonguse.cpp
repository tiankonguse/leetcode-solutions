/*************************************************************************
    > File Name: path-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 19 00:35:08 2019
    > link: https://leetcode.com/problems/path-sum/
    > No: 112. Path Sum
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    int sum;
    bool dfs(int now, TreeNode* root){

        //have left branch and go to leaf can get sum
        if(root->left != NULL && dfs(now + root->val, root->left)){
            return true;
        }

        //have rightbranch and go to leaf can get sum
        if(root->right != NULL && dfs(now + root->val, root->right)){
            return true;
        }

        //already go leaf, check sum
        if(root->left == NULL && root->right == NULL){
            return now + root->val == sum;
        }

        //return branch node
        return false;
    }
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if(root == NULL){
            return false;
        }
        this->sum = sum;
        return dfs(0, root);
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
    #define FUNCTION hasPathSum

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
