
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
  int countEffective(vector<int>& nums) {
    int n = nums.size();
    vector<ll> powers(n + 1, 1);
    powers[0] = 1;
    ll preOr = 0;
    for (int i = 1; i <= n; i++) {
      preOr |= nums[i - 1];
      powers[i] = (powers[i - 1] * 2) % mod;
    }
    int kMaxBit = 1;  // 10^6
    while ((1 << kMaxBit) <= preOr) {
      kMaxBit++;
    }

    const ll kMaxMask = 1 << kMaxBit;

    vector<ll> realBits;
    for (int i = 0; i < kMaxBit; i++) {
      if (preOr & (1 << i)) {
        realBits.push_back(i);
      }
    }
    int m = realBits.size();
    ll kRealMaxMask = 1 << m;

    auto getMask = [&](ll realMask) {
      ll mask = 0;
      for (int i = 0; i < m; i++) {
        if (realMask & (1 << i)) {
          mask |= (1 << realBits[i]);
        }
      }
      return mask;
    };

    ll ans = 0;
    for (int realMask = 1; realMask < kRealMaxMask; realMask++) {
      ll mask = getMask(realMask);
      ll oneCount = __builtin_popcount(mask);
      ll count_A = 0;  // 子集个数
      for (ll x : nums) {
        if ((x & mask) != 0) {
          count_A++;
        }
      }
      ll count_B = n - count_A;
      ll tmp = powers[count_B];
      if (oneCount % 2 == 1) {
        ans = (ans + tmp) % mod;
      } else {
        ans = (ans - tmp + mod) % mod;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& nums1, const int& ans) {  //
  TEST_SMP1(Solution, countEffective, ans, nums1);
}

int main() {
  Test({1, 2, 3}, 3);
  Test({7, 4, 6}, 4);
  Test({8, 8}, 1);
  Test({2, 2, 1}, 5);
  Test({2, 10, 6}, 6);
  return 0;
}

#endif