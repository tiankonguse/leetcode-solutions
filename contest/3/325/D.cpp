// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const ll mod = 1000000007;
class Solution {
  ll ans;
  int k;
  vector<ll> dp1, dp2;

  void Add(ll& a, ll b) { a = (a + b) % mod; }

  void Solver2(int v) {
    // 选择第一个数组，状态无变化，没有新增答案
    // 选择第二个数组，状态发生变化
    for (int i = k - 1; i >= 0; i--) {
      ll sum = i + v;
      if (sum >= k) {
        Add(ans, dp2[i]);
      } else {
        Add(dp2[sum], dp2[i]);
      }
    }
  }

  ll preSum = 0;
  void Solver1(int v) {
    // 选择第二个数组，第一个数组状态没变化，没有新增答案

    // 选择第一个数组，状态发生变化
    for (int i = k - 1; i >= 0; i--) {
      if (dp1[i] == 0) continue;
      ll sum = i + v;
      if (sum >= k) {  // 第一个数组满足条件
        ll left = preSum - sum;
        if (left >= k) {  // 第二个数组也满足条件
          Add(ans, dp1[i]);
        } else {  // 第二个数组不满足条件
          Add(dp2[left], dp1[i]);
        }
      } else {
        Add(dp1[sum], dp1[i]);
      }
    }
  }

 public:
  int countPartitions(vector<int>& nums, int k) {
    this->k = k;
    dp1.resize(k + 1, 0);
    dp2.resize(k + 1, 0);

    dp1[0] = 1;
    ans = 0;
    preSum = 0;

    for (auto v : nums) {
      preSum += v;
      Add(ans, ans);
      Solver2(v);
      Solver1(v);
    }
    return ans;
  }
};