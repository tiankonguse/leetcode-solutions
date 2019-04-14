/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 14 10:19:00 2019
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
    int dis(int a,int b){
        return a>b?a-b:b-a;
    }
    int dfs(TreeNode* root, int minVal, int maxVal){
        if(root == nullptr)return 0;
        int val = root->val;
        int ans = max(dis(minVal, val), dis(maxVal, val));
        ans = max(ans, dfs(root->left, min(val, minVal), max(val, maxVal)));
        ans = max(ans, dfs(root->right, min(val, minVal), max(val, maxVal)));
        return ans;

    }
public:
    int maxAncestorDiff(TreeNode* root) {
        return dfs(root, root->val, root->val);
    }
};
/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    TreeNode* first;
    int expectAns;

    first = vecToTree({8,3,10,1,6,null,14,null,null,4,7,13});
    expectAns = 7;
    TEST_SMP1(Solution, maxAncestorDiff, expectAns, first);


    return 0;
}
