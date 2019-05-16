/*************************************************************************
    > File Name: convert-sorted-array-to-binary-search-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 01:46:52 2019
    > link: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
    > No: 108. Convert Sorted Array to Binary Search Tree
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
    TreeNode* sortedArrayToBST(vector<int>& nums, int left = -1, int right = -1) {
        if(nums.size() == 0){
            return NULL;
        }
        if(left == -1){
            left = 0, right = nums.size()-1;
        }
        int mid = (left + right)/2;

        TreeNode* root = new TreeNode(nums[mid]);
        if(left<mid){
            root->left = sortedArrayToBST(nums, left, mid-1);
        }
        if(right >mid){
            root->right = sortedArrayToBST(nums, mid+1, right);
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
