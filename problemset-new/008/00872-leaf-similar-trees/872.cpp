
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
  vector<int>& dfs(TreeNode* root, vector<int>& v) {
    if(root == nullptr) return v;
    if(root->left == nullptr && root->right == nullptr) {
      v.push_back(root->val);
      return v;
    }
    dfs(root->left, v);
    dfs(root->right, v);
    return v;
  }

  public:
      bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> v1, v2;
          return dfs(root1, v1) == dfs(root2, v2);
      }
  };
#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif