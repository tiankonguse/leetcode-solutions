
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
 public:
  int specialTriplets(vector<int>& nums) {
    ll ans = 0;
    unordered_map<ll, ll> m1;
    unordered_map<ll, ll> m2;
    // 2v -> v -> 2v
    for (ll v2 : nums) {
      // 计算答案
      if (v2 % 2 == 0) {
        ll v = v2 / 2;
        if (m2.count(v)) {
          ans = (ans + m2[v]) % mod;
        }
      }
      // 计算 m2
      if (m1.count(v2 * 2)) {
        m2[v2] = (m2[v2] + m1[v2 * 2]) % mod;
      }
      // 计算 m1
      m1[v2]++;
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