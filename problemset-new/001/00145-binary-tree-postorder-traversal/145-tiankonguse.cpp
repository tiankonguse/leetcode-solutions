/*************************************************************************
    > File Name: binary-tree-postorder-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat May 18 23:53:18 2019
    > link: https://leetcode.com/problems/binary-tree-postorder-traversal/
    > No: 145. Binary Tree Postorder Traversal
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> sta;
        sta.push(root);
        while(!sta.empty()){
            TreeNode* now = sta.top();sta.pop();
            if(!now)continue;
            if(!now->left && !now->right){
                ans.push_back(now->val);
                continue;
            }
            TreeNode* left = now->left; now->left = NULL;
            TreeNode* right = now->right; now->right = NULL;
            sta.push(now);
            sta.push(right);
            sta.push(left);
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
    #define FUNCTION postorderTraversal

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
