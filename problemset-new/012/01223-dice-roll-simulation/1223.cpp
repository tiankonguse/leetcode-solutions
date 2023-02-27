// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
const int N = 6;
const int M = 17;
const int oneTimes = 1;
class Solution {
 public:
  int dieSimulator(int n, vector<int>& rollMax) {
    vector<ll> dp[N][M];
    for (int v = 0; v < N; v++) {
      for (int times = 0; times < M; times++) {
        dp[v][times].resize(n + 1, 0);
      }
    }

    for (int v = 0; v < N; v++) {
      dp[v][oneTimes][1] = 1;
    }

    vector<ll> sums(N, 0);
    for (int i = 2; i <= n; i++) {
      ll sum = 0;
      for (int v = 0; v < N; v++) {
        sums[v] = dp[v][oneTimes][i - 1];
        for (int times = 2; times <= rollMax[v]; times++) {
          dp[v][times][i] = dp[v][times - 1][i - 1];
          sums[v] = (sums[v] + dp[v][times][i - 1]) % mod;
        }
        sum = (sum + sums[v]) % mod;
      }
      for (int v = 0; v < N; v++) {
        dp[v][oneTimes][i] = (sum - sums[v] + mod) % mod;
      }
    }

    ll ans = 0;
    for (int v = 0; v < N; v++) {
      for (int times = 1; times <= rollMax[v]; times++) {
        ans = (ans + dp[v][times][n]) % mod;
      }
    }
    return ans;
  }
};
