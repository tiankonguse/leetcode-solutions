
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
  vector<vector<ll>> g;
  vector<ll> maxChildPath;
  vector<int> cost;
  ll Dfs(int u, int pre) {
    ll ans = 0;
    ll maxVal = 0;
    for (auto v : g[u]) {
      if (v == pre) continue;
      ans += Dfs(v, u);
      maxVal = max(maxVal, maxChildPath[v]);
    }
    for (auto v : g[u]) {
      if (v == pre) continue;
      if (maxVal != maxChildPath[v]) {
        ans++;
      }
    }
    maxChildPath[u] = maxVal + cost[u];
    return ans;
  }

 public:
  int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost_) {
    cost.swap(cost_);
    g.resize(n);
    maxChildPath.resize(n);
    for (auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    return Dfs(0, -1);
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