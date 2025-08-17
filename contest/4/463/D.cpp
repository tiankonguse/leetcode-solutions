
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
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }
class Solution {
 public:
  int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    vector<tuple<ll, ll, ll, ll, ll>> fixQuerys;
    fixQuerys.reserve(queries.size() * 2);
    for (auto& q : queries) {
      const int& li = q[0];
      int& ri = q[1];
      const int& ki = q[2];
      const int& vi = q[3];

      ri = li + (ri - li) / ki * ki;  // 修正右边界
      const ll offset = li % ki;
      fixQuerys.push_back({offset, ki, li, 1, vi});
      fixQuerys.push_back({offset, ki, ri + 1, -1, vi});
    }
    sort(fixQuerys.begin(), fixQuerys.end());

    ll preOffset = -1;
    ll preKi = -1;
    ll V = 1;
    ll offsetIndex = -1;
    for (const auto [offset, ki, idx, flag, vi] : fixQuerys) {
      if (preOffset != offset || preKi != ki) {
        preOffset = offset;
        preKi = ki;
        // 初始化
        offsetIndex = offset;
        V = 1;
      }

      while (offsetIndex < idx) {
        nums[offsetIndex] = (nums[offsetIndex] * V) % mod;
        offsetIndex += ki;
      }
      if (flag == 1) {  //
        V = (V * vi) % mod;
      } else {
        V = (V * inv(vi, mod)) % mod;
        // V = (V / vi) % mod;
      }
    }

    int ans = 0;
    for (auto v : nums) {
      ans ^= v;
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