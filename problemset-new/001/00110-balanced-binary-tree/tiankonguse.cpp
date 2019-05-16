/*************************************************************************
    > File Name: balanced-binary-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 01:44:50 2019
    > link: https://leetcode.com/problems/balanced-binary-tree/
    > No: 110: Balanced Binary Tree
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
    bool check(TreeNode* root, int& h){
        if(!root)return true;

        int leftH = 0, rightH = 0;
        if(!check(root->left, leftH)){
            return false;
        }
        if(!check(root->right, rightH)){
            return false;
        }
        if(leftH > rightH + 1 || rightH > leftH + 1){
            return false;
        }
        h = max(leftH, rightH) + 1;
        return true;
    }
public:
    bool isBalanced(TreeNode* root) {
        int h = 0;
        return check(root, h);
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
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
