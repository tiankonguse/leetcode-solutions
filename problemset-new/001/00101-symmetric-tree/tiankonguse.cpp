/*************************************************************************
    > File Name: symmetric-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 19 00:25:46 2019
    > link: https://leetcode.com/problems/symmetric-tree/
    > No: 101. Symmetric Tree
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
    bool eq(TreeNode* left, TreeNode* right){
        if(!left && !right)return true;
        if(!left || !right)return false;
        if(left->val != right->val)return false;
        return eq(left->left, right->right) && eq(left->right, right->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if(!root)return true;
        return eq(root->left, root->right);
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
    #define FUNCTION isSymmetric

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
