// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int ans = 0;
  int maxLev = 0;
  void Dfs(TreeNode* root, int lev) {
    if (root == nullptr) return;

    if (lev > maxLev) {
      maxLev = lev;
      ans = 0;
    }
    if (lev == maxLev) {
      ans += root->val;
    }
    Dfs(root->left, lev + 1);
    Dfs(root->right, lev + 1);
  }

 public:
  int deepestLeavesSum(TreeNode* root) {
    Dfs(root, 0);
    return ans;
  }
};
