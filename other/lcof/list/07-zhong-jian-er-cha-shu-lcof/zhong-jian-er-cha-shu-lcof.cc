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
class Solution {
  TreeNode* get(int v) { return new TreeNode(v); }
  TreeNode* dfs(int* pre, int* in, int len) {
    if (len == 0) {
      return NULL;
    }

    TreeNode* root = get(pre[0]);

    // find mid
    int mid = 0;
    while (in[mid] != pre[0]) {
      mid++;
    }

    // try left
    if (mid > 0) {
      root->left = dfs(pre + 1, in, mid);
    }

    // try right
    mid++;
    if (mid < len) {
      root->right = dfs(pre + mid, in + mid, len - mid);
    }

    return root;
  }

 public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.size() == 0) {
      return NULL;
    }
    return dfs(&preorder[0], &inorder[0], preorder.size());
  }
};

int main() {
  TEST_SMP2(Solution, buildTree, vecToTree({3, 9, 20, -1, -1, 15, 7}),
            vector<int>({3, 9, 20, 15, 7}), vector<int>({9, 3, 15, 20, 7}));
  TEST_SMP2(Solution, buildTree, vecToTree({}), vector<int>({}),
            vector<int>({}));
  TEST_SMP2(Solution, buildTree, vecToTree({1}), vector<int>({1}),
            vector<int>({1}));

  return 0;
}