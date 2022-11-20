#include <bits/stdc++.h>

#include "base.h"
using namespace std;

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
  vector<int> nums;
  void Dfs(TreeNode* root) {
    if (!root) return;
    nums.push_back(root->val);
    Dfs(root->left);
    Dfs(root->right);
  }

 public:
  vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
    nums.reserve(100000);
    Dfs(root);
    sort(nums.begin(), nums.end());

    vector<vector<int>> ans;
    ans.reserve(queries.size());
    for (auto v : queries) {
      int minVal = -1;
      int maxVal = -1;

      auto itMin = upper_bound(nums.begin(), nums.end(), v);
      if (itMin != nums.begin()) {
        itMin--;
        minVal = *itMin;
      }

      auto itMax = lower_bound(nums.begin(), nums.end(), v);
      if (itMax != nums.end()) {
        maxVal = *itMax;
      }

      ans.push_back({minVal, maxVal});
    }
    return ans;
  }
};
