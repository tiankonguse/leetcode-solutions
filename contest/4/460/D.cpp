
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

class LinearBasis {
  ll basisArray[32];  // 用于32位整数

 public:
  LinearBasis() { Init(); }
  void Init() { fill(basisArray, basisArray + 32, 0); }
  void InsertNumber(ll x) {
    for (int i = 31; i >= 0; --i) {
      if ((x >> i) & 1) {
        if (basisArray[i] == 0) {
          basisArray[i] = x;
          break;
        } else {
          x ^= basisArray[i];
        }
      }
    }
  }
  ll getMaxAndMask() {
    ll x = 0;
    for (int i = 31; i >= 0; --i) {
      if ((basisArray[i] ^ x) > x) {
        x ^= basisArray[i];
      }
    }
    return x;
  }
};

class Solution {
 public:
  long long maximizeXorAndXor(vector<int>& nums) {
    const int maxBits = 32;
    int n = nums.size();
    int N = 1 << n;

    ll totalXor = 0;
    for (auto value : nums) {
      totalXor ^= value;
    }
    ll ans = 0;
    const ll MaxVal = (1LL << 32) - 1;
    LinearBasis linearBasis;
    for (int mask = 0; mask < N; mask++) {  // 枚举 B
      ll andB = mask > 0 ? MaxVal : 0;
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
          andB &= nums[i];
        }
      }
      ll xorAC = totalXor;  // AC集合的异或
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
          xorAC ^= nums[i];
        }
      }
      // xorAC bit位为 1 的代表 AC 集合对一个的位有奇数个1，其他位有偶数个1
      // 性质1：奇数个1，不论如何选择，A 与 C 一个是奇数个1，一个是偶数个1，最终异或后求和还是 1
      // 性质2：偶数个1，不管怎么选择，xor(A) 与 xor(C) 都相等，故需要求出最大的 xor(A)
      const ll xorACEven = MaxVal ^ xorAC;
      linearBasis.Init();
      for (int i = 0; i < n; i++) {  // 枚举 A
        if (!(mask & (1 << i))) {
          linearBasis.InsertNumber(nums[i] & xorACEven);
        }
      }
      ans = max(ans, andB + xorAC + 2 * linearBasis.getMaxAndMask());
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