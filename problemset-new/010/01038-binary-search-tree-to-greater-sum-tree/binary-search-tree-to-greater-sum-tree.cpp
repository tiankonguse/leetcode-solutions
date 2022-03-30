/*************************************************************************
    > File Name: binary-search-tree-to-greater-sum-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月 7日  9:50:42
    > No: 1038. Binary Search Tree to Greater Sum Tree
    > Contest: 135
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
    int maxSum = 0;
public:
    TreeNode* bstToGst(TreeNode* root) {
        if(!root) {
            return root;
        }
        bstToGst(root->right);
        maxSum = root->val = root->val + maxSum;
        bstToGst(root->left);
        return root;
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
#define FUNCTION bstToGst

    TreeNode* first;
    TreeNode* expectAns;

    first = vecToTree({4,1,6,0,2,5,7,null,null,null,3,null,null,null,8});
    expectAns = vecToTree({30,36,21,36,35,26,15,null,null,null,33,null,null,null,8});
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
