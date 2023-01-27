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
  map<pair<TreeNode*, int>, int> m;
  int DfsEx(TreeNode* root, int dir) {  // 预期当前子树的方向
    if (root == nullptr) return 0;
    pair<TreeNode*, int> k = {root, dir};
    if (m.count(k)) {
      return m[k];
    }

    int ans = 1;
    if (dir == 0) {
      ans += DfsEx(root->left, 1 - dir);
    } else {
      ans += DfsEx(root->right, 1 - dir);
    }
    return m[k] = ans;
  }

  int Dfs(TreeNode* root) {
    if (root == nullptr) return 0;
    int ans = max(Dfs(root->left), Dfs(root->right));
    ans = max(ans, DfsEx(root, 0));
    ans = max(ans, DfsEx(root, 1));
    return ans;
  }

 public:
  int longestZigZag(TreeNode* root) {  //
    return Dfs(root) - 1;
  }
};
