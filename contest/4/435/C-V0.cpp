
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
ll Lcm(ll x, ll y) { return x / Gcd(x, y) * y; }

class Solution {
 public:
  int minimumIncrements(vector<int>& nums, vector<int>& target) {
    int n = nums.size();
    int m = target.size();

    const int M = 1 << m;
    vector<ll> lcms(M);
    lcms[0] = 1;
    for (int i = 0; i < m; i++) {
      const int MASK = 1 << i;
      for (int mask = 0; mask < MASK; mask++) {
        lcms[MASK | mask] = Lcm(target[i], lcms[mask]);
      }
    }

    // dp[i][MASK] = max(dp[i-1][sub] + Op(MASK ^ sub));
    vector dp(n + 1, vector<ll>(1 << m));
    dp[0][0] = 0;
    for (int i = 1; i < M; i++) {
      dp[0][i] = LLONG_MAX / 2;
    }

    for (int i = 1; i <= n; i++) {
      const int v = nums[i - 1];
      for (int j = 0; j < M; j++) {
        dp[i][j] = dp[i - 1][j];  // 不使用 v
        // 枚举 j 的子集，子集使用 v 得到答案，其他的使用前面的得到答案
        for (int sub = j; sub; sub = (sub - 1) & j) {
          const ll V = lcms[sub];
          const ll add = (V - v % V) % V;
          dp[i][j] = min(dp[i][j], dp[i - 1][j ^ sub] + add);
        }
      }
    }

    return dp[n][M - 1];
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