
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
enum { UP = 0, DOWN = 1 };
class Solution {
 public:
  int zigZagArrays(int n, int l, int r) {
    int R = r - l;
    if (n == 1) {
      return R + 1;
    }
    vector<vector<ll>> dp(2, vector<ll>(R + 1, 0));
    vector<vector<ll>> sum(2, vector<ll>(R + 1, 0));
    for (int i = 0; i <= R; i++) {
      dp[UP][i] = 1;
      dp[DOWN][i] = 1;
    }

    auto CalSUm = [&]() {
      fill(sum[UP].begin(), sum[UP].end(), 0);
      fill(sum[DOWN].begin(), sum[DOWN].end(), 0);
      sum[UP][0] = dp[UP][0] % mod;
      for (int i = 1; i <= R; i++) {
        sum[UP][i] = (sum[UP][i - 1] + dp[UP][i]) % mod;
      }
      sum[DOWN][R] = dp[DOWN][R] % mod;
      for (int i = R - 1; i >= 0; i--) {
        sum[DOWN][i] = (sum[DOWN][i + 1] + dp[DOWN][i]) % mod;
      }
    };

    CalSUm();

    n--;
    while (n--) {
      fill(dp[UP].begin(), dp[UP].end(), 0);
      fill(dp[DOWN].begin(), dp[DOWN].end(), 0);
      // UP -> DOWN
      for (int i = 1; i <= R; i++) {
        dp[DOWN][i] += sum[UP][i - 1];
      }
      // DOWN -> UP
      for (int i = R - 1; i >= 0; i--) {
        dp[UP][i] += sum[DOWN][i + 1];
      }
      CalSUm();
    }
    ll ans = 0;
    for (int i = 0; i <= R; i++) {
      ans = (ans + dp[UP][i] + dp[DOWN][i]) % mod;
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