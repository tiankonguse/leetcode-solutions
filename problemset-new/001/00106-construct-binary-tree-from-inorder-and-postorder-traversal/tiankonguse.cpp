/*************************************************************************
    > File Name: construct-binary-tree-from-inorder-and-postorder-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月21日 21:07:32
    > link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
    > No: 106. Construct Binary Tree from Inorder and Postorder Traversal
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
    TreeNode* buildTree(vector<int>& inorder, int inStart, int inEnd, vector<int>& postorder, int postStart, int postEnd) {
        if(inStart > inEnd) {
            return NULL;
        }
        if(inStart == inEnd) {
            return new TreeNode(inorder[inStart]);
        }

        //root
        int rootVal = postorder[postEnd];
        TreeNode* root = new TreeNode(rootVal);

        int inRootPos = inStart;
        for(; inorder[inRootPos] != rootVal; inRootPos++);

        if(inRootPos > inStart) { //have left
            int leftLen = inRootPos - inStart;
            root->left = buildTree(inorder, inStart, inRootPos-1, postorder, postStart, postStart + leftLen-1);
        }
        if(inRootPos < inEnd) { //have end
            int rightLen = inEnd - inRootPos;
            root->right = buildTree(inorder, inRootPos+1, inEnd, postorder, postEnd-rightLen, postEnd-1);
        }
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
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
#define FUNCTION buildTree

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
