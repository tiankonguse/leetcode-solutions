/*************************************************************************
    > File Name: binary-tree-level-order-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat May 18 23:55:38 2019
    > link: https://leetcode.com/problems/binary-tree-level-order-traversal/
    > No: 102. Binary Tree Level Order Traversal
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
    vector<vector<int> >ans;
    void init(int lev){
        if(ans.size() == lev){
            vector<int> line;
            ans.push_back(line);
        }
    }
    void dfs(int lev, TreeNode* root){
        if(root == NULL){
            return ;
        }

        init(lev);
        ans[lev].push_back(root->val);

        dfs(lev + 1, root->left);
        dfs(lev + 1, root->right);
    }
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        ans.clear();
        dfs(0, root);
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
