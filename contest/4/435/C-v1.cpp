
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
// GCD 相关算法

// 推论1：有俩个数p,q,且gcd(q,p)=1,则最大无法表示成px+qy（x>=0,y>=0)的数是pq-q-p.

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}
ll Lcm(ll x, ll y) {
  if (x == 0) x = 1;
  if (y == 0) y = 1;
  return x / Gcd(x, y) * y;
}

class Solution {
  vector<ll> buf;
  vector<int> target;
  vector<int> nums;
  vector<vector<ll>> dp;
  ll ans = LLONG_MAX;
  void Solver() {
    int m = buf.size();
    int n = nums.size();

    // dp[i][j] = min(dp[i-1][j], Cost(i,j) + dp[i-1][j-1])
    for (int i = 0; i <= n; i++) {
      dp[i][0] = 0;
      for (int j = 1; j <= m; j++) {
        dp[i][j] = LLONG_MAX / 2;
      }
    }

    for (int i = 1; i <= n; i++) {
      const int v = nums[i - 1];
      for (int j = 1; j <= m && j <= i; j++) {
        const ll V = buf[j - 1];
        const ll add = (V - v % V) % V;
        dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + add);
      }
    }

    ans = min(ans, dp[n][m]);
  }
  void Dfs(const ll pre) {
    if (target.empty()) {
      if (pre) buf.push_back(pre);
      Solver();
      if (pre) buf.pop_back();
      return;
    }

    const int m = target.size();
    for (int i = 0; i < m; i++) {  // 选择 i
      const ll selectVal = target[i];

      swap(target[i], target.back());
      target.pop_back();

      Dfs(Lcm(pre, selectVal));

      target.push_back(selectVal);
      swap(target[i], target.back());
    }

    // 选择结束
    if (pre) {
      buf.push_back(pre);
      Dfs(0);
      buf.pop_back();
    }
  }

 public:
  int minimumIncrements(vector<int>& nums_, vector<int>& target_) {
    target.swap(target_);
    nums.swap(nums_);
    dp.resize(nums.size() + 1, vector<ll>(target.size() + 1, LLONG_MAX / 2));
    Dfs(0);
    return ans;
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