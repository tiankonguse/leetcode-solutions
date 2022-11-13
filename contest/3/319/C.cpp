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
  vector<vector<int>> nums;

  int DfsDeep(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + max(DfsDeep(root->left), DfsDeep(root->right));
  }
  void DfsVal(TreeNode* root, int lev) {
    if (root == nullptr) return;
    nums[lev].push_back(root->val);
    DfsVal(root->left, lev + 1);
    DfsVal(root->right, lev + 1);
  }

  int SolverEx(vector<int>& nums) {
    int ans = 0;

    map<int, int> m;
    int n = nums.size();

    if (n <= 1) return ans;

    printf("num=%d ", n);
    for (int i = 0; i < n; i++) {
      m[nums[i]] = i;
      printf(" %d=>%d ", nums[i], i);
    }
    printf("\n");

    int index = 0;
    while (m.size() > 1) {
      auto [minVal, minValPos] = *m.begin();
      if (index == minValPos) {  // 最小值已经在第一个位置了
        m.erase(minVal);
        index++;
        continue;
      }

      int indexVal = nums[index];

      nums[index] = minVal;
      nums[minValPos] = indexVal;
      m[indexVal] = minValPos;

      m.erase(minVal);
      ans++;
      index++;
    }

    return ans;
  }

  int Solver() {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      ans += SolverEx(nums[i]);
    }
    return ans;
  }

 public:
  int minimumOperations(TreeNode* root) {
    int h = DfsDeep(root);
    nums.resize(h);
    DfsVal(root, 0);

    return Solver();
  }
};