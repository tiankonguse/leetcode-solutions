/*************************************************************************
    > File Name: binary-tree-maximum-path-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月 8日 12:58:52
    > link: https://leetcode.com/problems/binary-tree-maximum-path-sum/
    > No: 124. Binary Tree Maximum Path Sum
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

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
    int maxAns;
    typedef TreeNode T;
    int dfs(T* root) {
        if(!root) {
            return -1;
        }

        int nowVal = root->val;
        int leftVal = dfs(root->left);
        int rightVal = dfs(root->right);

        maxAns = max(maxAns, nowVal); //root
        maxAns = max(maxAns, nowVal + leftVal); //root + left
        maxAns = max(maxAns, nowVal + rightVal);//root + right
        maxAns = max(maxAns, nowVal + rightVal + leftVal); //left + root + right

        int retVal = nowVal;
        retVal = max(retVal, nowVal + leftVal);
        retVal = max(retVal, nowVal + rightVal);
        return retVal;
    }

public:
    int maxPathSum(TreeNode* root) {
        maxAns = root->val;
        dfs(root);
        return maxAns;
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
#define FUNCTION maxPathSum

    TreeNode* first;
    int expectAns;

    first = vecToTree({1,2,3});
    expectAns = 6;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = vecToTree({-10,9,20,null,null,15,7});
    expectAns = 42;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
