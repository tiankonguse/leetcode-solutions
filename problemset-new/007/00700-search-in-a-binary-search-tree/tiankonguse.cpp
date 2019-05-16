/*************************************************************************
    > File Name: search-in-a-binary-search-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 00:51:58 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(!root)return NULL;
        if(root->val == val)return root;
        if(root->val < val){
            return searchBST(root->right, val);
        }else{
            return searchBST(root->left, val);
        }
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
    #define FUNCTION searchBST

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
