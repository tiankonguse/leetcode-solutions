
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
  pair<int, int> Dfs(TreeNode* root) {  // <数量, 子树最大值>
    if (root == nullptr) return {0, 0};
    auto [leftCount, leftMax] = Dfs(root->left);
    auto [rightCount, rightMax] = Dfs(root->right);
    int currentMax = max({leftMax, rightMax, root->val});
    int currentCount = leftCount + rightCount;
    if (root->val == currentMax) currentCount++;
    return {currentCount, currentMax};
  }

 public:
  int countDominantNodes(TreeNode* root) {
    auto [count, _] = Dfs(root);
    return count;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif