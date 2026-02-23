
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

  vector<int> nums;
  ll K;
  int n;
  map<tuple<int, ll, ll>, ll> memo;
  ll Dfs(int p, ll A, ll B) {
    auto [a, b] = Smp(A, B);
    if (p == n) {
      return a == K && b == 1 ? 1 : 0;
    }
    auto key = make_tuple(p, a, b);
    if (memo.count(key)) {
      return memo[key];
    }
    ll ret = Dfs(p + 1, a * nums[p], b) + Dfs(p + 1, a, b * nums[p]) + Dfs(p + 1, a, b);
    memo[key] = ret;
    return ret;
  }

 public:
  // 方法：暴力枚举+剪枝， 87ms
  int countSequences(vector<int>& nums_, ll k) {
    nums.swap(nums_);
    K = k;
    n = nums.size();
    return Dfs(0, 1, 1);
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