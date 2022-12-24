// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  vector<int> nums;
  vector<int> bits;
  vector<int> dp;
  int N;
  int MASK;
  void Init() {
    n = nums.size();
    N = 1 << n;
    MASK = N - 1;
    dp.resize(N, -1);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int mask = (1 << i) | (1 << j);
        bits.push_back(mask);
        dp[mask] = gcd(nums[i], nums[j]);
      }
    }
  }

  int Dfs(int mask, int t) {
    int& ret = dp[mask];
    if (ret != -1) return ret;

    ret = 0;
    for (auto b : bits) {
      if ((mask & b) != b) continue;
      ret = max(ret, Dfs(mask ^ b, t - 1) + t * dp[b]);
    }
    return ret;
  }

 public:
  int maxScore(vector<int>& nums_) {
    nums.swap(nums_);
    Init();
    return Dfs((1 << n) - 1, n / 2);
  }
};
