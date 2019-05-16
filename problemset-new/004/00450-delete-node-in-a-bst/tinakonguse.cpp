/*************************************************************************
    > File Name: delete-node-in-a-bst.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 01:06:15 2019
    > link: https://leetcode.com/problems/delete-node-in-a-bst/
    > No: 450. Delete Node in a BST
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
    TreeNode* deleteSmallNode(TreeNode* root, TreeNode*& preNext){
        if(!root->left){
            preNext = root->right;
            return root;
        }
        return deleteSmallNode(root->left, root->left);
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root)return root;
        //root is key
        if(root->val == key){
            if(!root->left)return root->right;
            if(!root->right)return root->left;
            TreeNode* newRoot = deleteSmallNode(root->right, root->right);
            newRoot->left = root->left;
            newRoot->right = root->right;
            return newRoot;
        }
        if(root->val < key){
            root->right = deleteNode(root->right, key);
        }else{
            root->left = deleteNode(root->left, key);
        }
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
    #define FUNCTION deleteNode

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
