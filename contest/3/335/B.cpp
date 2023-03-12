
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
  int DfsLev(TreeNode* root) {
    if (root == nullptr) return 0;
    return max(DfsLev(root->left), DfsLev(root->right)) + 1;
  }

  vector<ll> sums;
  void Dfs(TreeNode* root, int lev) {
    if (root == nullptr) return;
    sums[lev] += root->val;
    Dfs(root->left, lev + 1);
    Dfs(root->right, lev + 1);
  }

 public:
  long long kthLargestLevelSum(TreeNode* root, int k) {
    int maxLev = DfsLev(root);
    if (maxLev < k) return -1;
    sums.resize(maxLev);

    Dfs(root, 0);
    sort(sums.begin(), sums.end(), [](auto a, auto b) { return a > b; });
    return sums[k - 1];
  }
};