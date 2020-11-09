/*************************************************************************
    > File Name: construct-binary-tree-from-preorder-and-inorder-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月21日 21:18:05
    > link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
    > No: 105. Construct Binary Tree from Preorder and Inorder Traversal
    > Contest:
 ************************************************************************/

#include "base.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//前序遍历 preorder = [3,9,20,15,7]
//中序遍历 inorder = [9,3,15,20,7]
class Solution {
    TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd) {
        if(preStart > preEnd) {
            return NULL;
        }
        if(preStart == preEnd) {
            return new TreeNode(preorder[preStart]);
        }
        //root
        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);

        int inRootPos = inStart;
        for(; inorder[inRootPos] != rootVal; inRootPos++);

        if(inRootPos > inStart) { // have left
            int leftLen = inRootPos - inStart;
            root->left = buildTree(preorder, preStart+1, preStart + leftLen, inorder, inStart, inRootPos - 1);
        }
        if(inRootPos < inEnd) { // have right
            int rightLen = inEnd - inRootPos;
            root->right = buildTree(preorder,preEnd-rightLen+1,  preEnd, inorder, inRootPos+1, inEnd);
        }
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
};
/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
  TEST_SMP2(Solution, buildTree, vecToTree({3, 9, 20, -1, -1, 15, 7}),
            vector<int>({3, 9, 20, 15, 7}), vector<int>({9, 3, 15, 20, 7}));
  TEST_SMP2(Solution, buildTree, vecToTree({}), vector<int>({}),
            vector<int>({}));
  TEST_SMP2(Solution, buildTree, vecToTree({1}), vector<int>({1}),
            vector<int>({1}));

    return 0;
}
