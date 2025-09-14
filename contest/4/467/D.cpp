
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
class Solution {
  enum { E_EMPTY, E_0, E_1, E_00, E_01, E_10, E_11, E_OTHER, E_END };
  int NextState(int s, int v) {
    if (s == E_EMPTY) {
      return E_0 + v;
    } else if (s == E_0 || s == E_1) {
      return E_00 + (s - E_0) * 2 + v;
    } else if (s == E_OTHER) {
      return E_OTHER;
    } else {
      int tmp = (s - E_00) * 2 + v;
      if (tmp == 0 || tmp == 7) {
        return E_OTHER;
      } else {
        return E_00 + (tmp % 4);
      }
    }
  }

 public:
  int countStableSubsequences(vector<int>& nums) {
    // $, $0, $1, $00, $01, $10, $11
    vector<ll> dp(E_END, 0);
    dp[E_EMPTY] = 1;
    vector<ll> next(E_END, 0);
    for (auto v : nums) {
      v = v % 2;
      fill(next.begin(), next.end(), 0);
      for (int i = 0; i < E_END; i++) {
        int s = NextState(i, v);
        next[s] = (next[s] + dp[i]) % mod;
      }
      for (int i = 0; i < E_END; i++) {
        dp[i] = (dp[i] + next[i]) % mod;
      }
    }
    ll ans = 0;
    for (int i = E_0; i <= E_11; i++) {
      ans = (ans + dp[i]) % mod;
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