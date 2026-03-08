
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
  ll encCost, flatCost;
  vector<ll> pre;
  ll Dfs(int l, int r) {
    ll L = r - l + 1;
    ll X = pre[r] - pre[l - 1];
    ll ans = X == 0 ? flatCost : L * X * encCost;
    if (L % 2 == 1) {
      return ans;
    }
    ll tmp = Dfs(l, l + L / 2 - 1) + Dfs(l + L / 2, r);
    return min(ans, tmp);
  }

 public:
  ll minCost(const string& s, int encCost, int flatCost) {
    int n = s.size();
    this->encCost = encCost;
    this->flatCost = flatCost;
    pre.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      const int v = s[i - 1] - '0';
      pre[i] = pre[i - 1] + v;
    }
    return Dfs(1, n);
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