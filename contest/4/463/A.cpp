
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
constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
class Solution {
 public:
  long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
    int n = prices.size();
    vector<ll> preSum(n + 2, 0), pricesSum(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      preSum[i] = preSum[i - 1] + prices[i - 1] * strategy[i - 1];
    }
    for (int i = 1; i <= n; i++) {
      pricesSum[i] = pricesSum[i - 1] + prices[i - 1];
    }
    ll ans = preSum[n];
    for (int i = 1; i + k - 1 <= n; i++) {
      int k2 = k / 2;
      int L = i - 1, R = i + k;     // [1, L] [R, n]
      int SL = i + k2, SR = R - 1;  // [SL, SR]
      ll sum = 0;
      sum += preSum[L] - preSum[0];
      sum += preSum[n] - preSum[R - 1];
      sum += pricesSum[SR] - pricesSum[SL - 1];

      ans = max(ans, sum);
    }
    return ans;
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