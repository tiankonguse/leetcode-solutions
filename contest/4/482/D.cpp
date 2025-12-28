
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
class Solution {
  string sx;
  int len;
  map<pair<int, int>, ll> dp;
  ll DfsFull(int p, int dis) {  // 前 p 位随便填充，使得前缀差为 dis 时的方案数
    pair<int, int> key = {p, dis};
    if (dp.count(key)) return dp[key];
    if (p < 0) return dis == 0 ? 1 : 0;
    ll& ans = dp[key];
    ans = 0;
    for (int i = 0; i < 10; i++) {
      ans += DfsFull(p - 1, Cal(p, dis, i));
    }
    return ans;
  }
  ll Cal(int p, int dis, int V) {
    if (p % 2 == 0) {
      return dis + V;
    } else {
      return dis - V;
    }
  }
  ll DfsEq(int p, ll dis) {
    if (p < 0) return dis == 0 ? 1 : 0;
    ll ans = 0;
    // 奇数加，偶数减
    const int V = sx[p] - '0';
    for (int i = 0; i < V; i++) {
      ans += DfsFull(p - 1, Cal(p, dis, i));
    }
    ans += DfsEq(p - 1, Cal(p, dis, V));
    return ans;
  }
  ll countBalanced(ll x) {
    ll ans = 0;
    sx = to_string(x);
    std::reverse(sx.begin(), sx.end());
    len = sx.length();
    return DfsEq(len - 1, 0);
  }

 public:
  ll countBalanced(ll low, ll high) {  //
    return countBalanced(high) - countBalanced(low - 1);
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