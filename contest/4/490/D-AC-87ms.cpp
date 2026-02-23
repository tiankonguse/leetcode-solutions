
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
ll gcd(ll a, ll b) {
  while (a != 0) {
    ll tmp = a;
    a = b % a;
    b = tmp;
  }
  return b;
}

class Solution {
  pair<ll, ll> Smp(ll a, ll b) {
    ll g = gcd(a, b);
    return {a / g, b / g};
  }

 public:
  // 方法：暴力枚举+剪枝， 87ms
  int countSequences(vector<int>& nums, ll k) {
    int n = nums.size();
    vector<ll> suffSum(n + 2, 1);
    for (int i = n - 1; i >= 0; i--) {
      suffSum[i] = suffSum[i + 1] * nums[i];
    }

    map<pair<ll, ll>, ll> pre;
    pre[{1, 1}] = 1;
    for (int i = 0; i < n; i++) {
      ll v = nums[i];
      map<pair<ll, ll>, ll> cur;
      for (auto [p, c] : pre) {
        auto [a, b] = p;
        ll suff = suffSum[i + 1];
        // 乘法
        if (a * v * suff % b == 0 && a * v * suff / b >= k) {
          cur[Smp(a * v, b)] += c;
        }
        // 除法
        if (a * suff % (b * v) == 0 && a * suff / (b * v) >= k) {
          cur[Smp(a, b * v)] += c;
        }
        // 不选择
        if (a * suff % b == 0 && a * suff / b >= k) {
          cur[p] += c;
        }
      }
      pre = std::move(cur);
    }
    return pre[{k, 1}];
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