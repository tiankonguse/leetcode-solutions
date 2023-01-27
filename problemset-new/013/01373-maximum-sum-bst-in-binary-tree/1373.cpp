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
  int ans = 0;

  tuple<bool, int, int, int> Dfs(TreeNode* root) {
    int minVal = root->val;
    int maxVal = root->val;
    int sumVal = root->val;
    bool result = true;

    if (root->left) {
      auto [leftResult, leftMin, leftMax, leftSum] = Dfs(root->left);
      if (leftResult && leftMax < root->val) {
        minVal = leftMin;
        sumVal += leftSum;
      } else {
        result = false;
      }
    }

    if (root->right) {
      auto [rightResult, rightMin, rightMax, rightSum] = Dfs(root->right);
      if (rightResult && root->val < rightMin) {
        maxVal = rightMax;
        sumVal += rightSum;
      } else {
        result = false;
      }
    }

    if (result) {
      ans = max(ans, sumVal);
    }
    return {result, minVal, maxVal, sumVal};
  }

 public:
  int maxSumBST(TreeNode* root) {
    Dfs(root);
    return ans;
  }
};