/*************************************************************************
    > File Name: insert-into-a-binary-search-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 00:54:40 2019
    > link: https://leetcode.com/problems/insert-into-a-binary-search-tree/
    > No: 701. Insert into a Binary Search Tree
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root){
            return new TreeNode(val);
        }
        if(root->val > val){
            if(root->left){
                insertIntoBST(root->left, val);
            }else{
                root->left = new TreeNode(val);
            }
        }else{
            if(root->right){
                insertIntoBST(root->right, val);
            }else{
                root->right = new TreeNode(val);
            }
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
    #define FUNCTION insertIntoBST

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
