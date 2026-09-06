
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;

// 快速幂
ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}
const ll mod = 1e9 + 7;
class Solution {
 public:
  int sumDecoded(vector<ll>& nums) {
    ll ans = 0;
    for (const ll v : nums) {
      const ll w = v % 10;
      const ll d = floor(v / 10);
      const string s = to_string(d);
      ll bit = s.size();
      ll x = 0;  // [0,w)
      for (int i = 0; i < w; i++) {
        x = x * 10 + (s[i] - '0');
      }
      ll y = 0;
      for (int i = w; i < bit; i++) {
        y = y * 10 + (s[i] - '0');
      }
      ll V = qpow(x, y, mod);
      ans = (ans + V) % mod;
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