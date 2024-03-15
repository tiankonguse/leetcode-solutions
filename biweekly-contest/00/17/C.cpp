// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
  int Dfs(TreeNode* root, int pre, int prepre) {
    if (root == nullptr) return 0;

    int ans = 0;
    if (prepre != -1 && prepre % 2 == 0) {
      ans += root->val;
    }
    ans += Dfs(root->left, root->val, pre);
    ans += Dfs(root->right, root->val, pre);

    return ans;
  }

 public:
  int sumEvenGrandparent(TreeNode* root) { return Dfs(root, -1, -1); }
};