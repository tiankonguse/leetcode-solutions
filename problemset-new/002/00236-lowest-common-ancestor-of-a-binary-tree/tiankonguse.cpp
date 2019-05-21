/*************************************************************************
    > File Name: lowest-common-ancestor-of-a-binary-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月21日 21:56:58
    > link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
    > No: 236. Lowest Common Ancestor of a Binary Tree
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
    typedef TreeNode T;
    T* dfs(T* root, T* p, T* q){
        if(!root)return root;
        if(root == p || root == q)return root;
        T* left = dfs(root->left, p, q);
        T* right = dfs(root->right, p, q);
        if(left && right)return root;
        if(left)return left;
        if(right)return right;
        return NULL;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return dfs(root, p, q);
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
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
