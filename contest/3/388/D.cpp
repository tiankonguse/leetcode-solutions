// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 50;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
class Solution {
 public:
  ll maximumStrength(const vector<int>& nums, const int K) {
    const int N = nums.size();
    vector<vector<vector<ll>>> f(
        2, vector<vector<ll>>(N + 1, vector<ll>(K + 1, -INFL)));
    vector<vector<vector<ll>>> F(
        2, vector<vector<ll>>(N + 1, vector<ll>(K + 1, -INFL)));

    ll sign[2] = {-1, 1};
    for (int n = N - 1; n >= 0; n--) {
      for (int k = 1; k <= K; k++) {
        for (int i = 0; i < 2; i++) {
          if (N - n < k) continue;
          // 选择一个
          ll V = nums[n] * sign[i] * k;

          if (n == N - 1) {  // n == N-1 && k == 1
            F[i][n][k] = V;
            f[i][n][k] = V;
          } else if (k == 1) {  // n < N-1 && k == 1
            F[i][n][k] = max(V, V + F[i][n + 1][k]);
            f[i][n][k] = max(f[i][n + 1][k], F[i][n][k]);
          } else if (N - n == k) {  //
            F[i][n][k] = V + F[1 - i][n + 1][k - 1];
            f[i][n][k] = V + F[1 - i][n + 1][k - 1];
          } else {  // n < N-1 && k > 1
            F[i][n][k] = V + max(f[1 - i][n + 1][k - 1], F[i][n + 1][k]);
            f[i][n][k] = max(f[i][n + 1][k], F[i][n][k]);
          }

          printf("V=%lld F left=%lld F right=%lld f left=%lld f right=%lld\n",
                 f[1 - i][n + 1][k - 1], F[i][n + 1][k], f[i][n + 1][k],
                 F[i][n][k]);
          printf("i=%d n=%d k=%d F=%lld f=%lld\n", i, n, k, F[i][n][k],
                 f[i][n][k]);
        }
      }
    }
    return f[1][0][K];
  }
};