// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll Gcd(ll x, ll y) { return gcd(x, y); }
class Solution {
  int Check(vector<int>& nums) {
    int a = nums.front();
    for (auto v : nums) {
      a = Gcd(a, v);
    }
    return a;
  }
  vector<int> nums;
  vector<vector<int>> dp;
  vector<vector<int>> gcgVal;
  vector<vector<int>> minGcdOne;
  int n;
  void Init() {
    gcgVal.resize(n, vector<int>(n, -1));
    minGcdOne.resize(n, vector<int>(n, INT_MAX));
    dp.resize(n, vector<int>(n, -2));
    for (int i = 0; i < n; i++) {
      int a = nums[i];
      for (int j = i; j < n; j++) {
        a = Gcd(a, nums[j]);
        gcgVal[i][j] = a;
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (gcgVal[i][j] != 1) {
          minGcdOne[i][j] = INT_MAX;
          continue;
        }
        if (i == j) {
          minGcdOne[i][j] = 1;
          continue;
        }

        minGcdOne[i][j] = minGcdOne[i][j - 1];
        for (int k = i; k <= j; k++) {
          if (gcgVal[k][j] == 1) {
            minGcdOne[i][j] = min(minGcdOne[i][j], j - k + 1);
          }
        }
      }
    }
  }

  // 贪心
  int Solver(int l, int r) {
    int len = r - l + 1;
    return (minGcdOne[l][r] - 1) + len - 1;
  }

  int Dfs(int l, int r) {
    int& ret = dp[l][r];
    if (ret != -2) {
      return ret;  // 计算过了
    }

    if (gcgVal[l][r] != 1) {
      return ret = -1;  // 当前区间无法变成 1
    }

    if (l == r) {
      return ret = 0;
    }

    // 方法 1： 不拆分，即进入贪心策略
    ret = Solver(l, r);

    // 方法 2：拆分
    for (int i = l; i < r; i++) {
      int lv = Dfs(l, i);
      int rv = Dfs(i + 1, r);
      if (lv != -1 && rv != -1) {
        ret = min(ret, lv + rv);
      }
    }
    return ret;
  }

 public:
  int minOperations(vector<int>& nums_) {
    nums.swap(nums_);
    n = nums.size();
    Init();
    if (gcgVal[0][n - 1] != 1) {
      return -1;
    }
    return Dfs(0, n - 1);
  }
};