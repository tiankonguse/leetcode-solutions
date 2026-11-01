
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
  struct Node {
    ll v;
    ll c;
    ll x;
    Node(ll v = 0, ll c = 0, ll x = 0) : v(v), c(c), x(x) {}
  };
  vector<vector<Node>> g;
  vector<int> values;
  ll Xor(ll a, ll b) {
    ll c = a ^ b;
    return __builtin_popcount(c) % 2;
  }

  vector<vector<ll>> dp;  // INT64_MAX 代表不存在
  void Dfs0(int u, int pre) {
    for (auto& node : g[u]) {
      if (node.v == pre) continue;
      int v = node.v;
      ll c = node.c;
      Dfs0(v, u);
      if (node.x == 0) {
        dp[u][0] = min(dp[u][0], c);
        if (dp[v][0] != INT64_MAX) {
          dp[u][1] = min(dp[u][1], c + dp[v][0]);
        }
      } else {
        dp[u][1] = min(dp[u][1], c);
        if (dp[v][0] != INT64_MAX) {
          dp[u][0] = min(dp[u][0], c + dp[v][0]);
        }
      }
    }
  }
  ll ans;
  void DfsRoot(const int u, const int pre, const ll pre0 = INT64_MAX, const ll pre1 = INT64_MAX) {
    ll uAns = min(dp[u][0], pre0);
    ans = min(ans, uAns);
    vector<pair<ll, ll>> child0(2, {pre0, pre});
    vector<pair<ll, ll>> child1(2, {pre1, pre});  // 保留最小的 2 个值
    for (auto& node : g[u]) {
      if (node.v == pre) continue;
      int v = node.v;
      ll c = node.c;
      ll v0 = INT64_MAX;
      ll v1 = INT64_MAX;
      if (node.x == 0) {
        v0 = min(v0, c);
        if (dp[v][0] != INT64_MAX) {
          v1 = min(v1, c + dp[v][0]);
        }
      } else {
        v1 = min(v1, c);
        if (dp[v][0] != INT64_MAX) {
          v0 = min(v0, c + dp[v][0]);
        }
      }
      if (v0 != INT64_MAX) {
        child0.push_back({v0, v});
        sort(child0.begin(), child0.end());
        if (child0.size() > 2) child0.pop_back();
      }
      if (v1 != INT64_MAX) {
        child1.push_back({v1, v});
        sort(child1.begin(), child1.end());
        if (child1.size() > 2) child1.pop_back();
      }
    }
    for (auto& node : g[u]) {
      if (node.v == pre) continue;
      int v = node.v;
      ll c = node.c;
      ll u0 = child0[0].first;
      if (child0[0].second == v) {
        u0 = child0[1].first;
      }
      ll u1 = child1[0].first;
      if (child1[0].second == v) {
        u1 = child1[1].first;
      }
      ll v0 = INT64_MAX;
      ll v1 = INT64_MAX;
      if (node.x == 0) {
        v0 = min(v0, c);
        if (u0 != INT64_MAX) {
          v1 = min(v1, c + u0);
        }
      } else {
        v1 = min(v1, c);
        if (u0 != INT64_MAX) {
          v0 = min(v0, c + u0);
        }
      }
      DfsRoot(v, u, v0, v1);
    }
  }

 public:
  int minActivationCost(vector<vector<int>>& edges, vector<int>& values_) {
    values.swap(values_);
    int n = values.size();
    g.resize(n);
    for (auto& e : edges) {
      ll u = e[0];
      ll v = e[1];
      ll c = e[2];
      ll x = Xor(values[u], values[v]);
      g[u].push_back({v, c, x});
      g[v].push_back({u, c, x});
    }
    dp.resize(n, vector<ll>(2, INT64_MAX));
    Dfs0(0, -1);
    ans = dp[0][0];
    DfsRoot(0, -1);
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