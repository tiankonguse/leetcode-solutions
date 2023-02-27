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
  vector<vector<int>> g;
  void DfsTree(TreeNode* root, int pre) {
    if (root == nullptr) return;
    int val = root->val;
    if (pre != -1) {
      g[pre].push_back(val);
      g[val].push_back(pre);
    }
    DfsTree(root->left, root->val);
    DfsTree(root->right, root->val);
  }

  vector<int> nums;
  int DfsCount(int now, int p) {
    nums[now] = 1;
    for (auto c : g[now]) {
      if (c == p) continue;
      nums[now] += DfsCount(c, now);
    }
    return nums[now];
  }

 public:
  bool btreeGameWinningMove(TreeNode* root, int n, int x) {
    g.resize(n + 1);
    DfsTree(root, -1);
    nums.resize(n + 1, 0);
    DfsCount(x, -1);

    int maxVal = 0;
    for (auto c : g[x]) {
      maxVal = max(maxVal, nums[c]);
    }
    return maxVal > n - maxVal;
  }
};