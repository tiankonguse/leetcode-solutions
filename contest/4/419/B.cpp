// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

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

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
  min_queue<ll> que;
  int k;
  ll Dfs(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }

    ll num = -1;
    ll left = Dfs(root->left);
    ll right = Dfs(root->right);
    if (left != -1 && left == right) {
      num = 1 + left + right;
      que.push(num);
      if (que.size() > k) {
        que.pop();
      }
    }
    return num;
  }

 public:
  int kthLargestPerfectSubtree(TreeNode* root, int k) {
    this->k = k;
    Dfs(root);
    if (que.size() != k) {
      return -1;
    }
    return que.top();
  }
};