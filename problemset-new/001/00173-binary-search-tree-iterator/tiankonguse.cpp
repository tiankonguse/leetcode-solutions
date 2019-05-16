/*************************************************************************
    > File Name: binary-search-tree-iterator.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 00:34:20 2019
    > link: https://leetcode.com/problems/binary-search-tree-iterator/
    > No: 173. Binary Search Tree Iterator
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
class BSTIterator {
    stack<TreeNode*> sta;
    void add(TreeNode* root) {
        while(root) {
            sta.push(root);
            root = root->left;
        }
    }
public:
    BSTIterator(TreeNode* root) {
        add(root);
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* root = sta.top();
        sta.pop();
        add(root->right);
        return root->val;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !sta.empty();
    }
};
