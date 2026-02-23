
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

// 辗转相除法
// 复杂度 O(log(min(a,b)))
__int128_t gcd(__int128_t a, __int128_t b) {
  while (a != 0) {
    __int128_t tmp = a;
    a = b % a;
    b = tmp;
  }
  return b;
}

class Solution {
  pair<__int128_t, __int128_t> Smp(__int128_t a, __int128_t b) {
    __int128_t g = gcd(a, b);
    return {a / g, b / g};
  }

 public:
  // 方法2：折半 67ms
  int countSequences(vector<int>& nums, ll k) {
    int n = nums.size();
    map<pair<__int128_t, __int128_t>, ll> pre;
    pre[{1, 1}] = 1;
    for (int i = 0; i < n / 2; i++) {
      __int128_t v = nums[i];
      map<pair<__int128_t, __int128_t>, ll> cur;
      for (auto [p, c] : pre) {
        // 乘法
        cur[Smp(p.first * v, p.second)] += c;
        // 除法
        cur[Smp(p.first, p.second * v)] += c;
        // 不选择
        cur[p] += c;
      }
      pre = std::move(cur);
    }

    map<pair<__int128_t, __int128_t>, ll> suff;
    suff[{k, 1}] = 1;
    for (int i = n - 1; i >= n / 2; i--) {
      __int128_t v = nums[i];
      map<pair<__int128_t, __int128_t>, ll> cur;
      for (auto [p, c] : suff) {
        // 乘法
        cur[Smp(p.first * v, p.second)] += c;
        // 除法
        cur[Smp(p.first, p.second * v)] += c;
        // 不选择
        cur[p] += c;
      }
      suff = std::move(cur);
    }
    ll ans = 0;
    for (auto [p, c] : pre) {
      if (suff.count(p)) {
        ans += c * suff[p];
      }
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