/*************************************************************************
    > File Name: binary-tree-preorder-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat May 18 23:42:39 2019
    > link: https://leetcode.com/problems/binary-tree-preorder-traversal/
    > No: 144. Binary Tree Preorder Traversal
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
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>  ans;
        stack<TreeNode*> sta;
        sta.push(root);

        while(!sta.empty()){
            TreeNode* now = sta.top();sta.pop();
            if(now == NULL){
                continue;
            }
            ans.push_back(now->val);
            sta.push(now->right);
            sta.push(now->left);
        }
        return ans;
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
    #define FUNCTION preorderTraversal

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
