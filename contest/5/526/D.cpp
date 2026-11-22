
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
const ll INT64_MAX2 = INT64_MAX / 2;
class Solution {
  struct Node {
    ll v;
    ll c;
    Node(ll v = 0, ll c = 0) : v(v), c(c) {}
  };
  vector<vector<Node>> g;
  vector<int> values;

  vector<vector<ll>> dp;  // INT64_MAX2 代表不存在
  void Dfs0(int u, int pre) {
    const int uv = values[u];
    dp[u][uv] = 0;
    for (auto& node : g[u]) {
      if (node.v == pre) continue;
      int v = node.v;
      ll c = node.c;
      const int vv = values[v];
      Dfs0(v, u);
      if (uv == 0) {
        dp[u][1] = min(dp[u][1], min(dp[v][1] + c, INT64_MAX2));
      }
    }
    MyPrintf("Dfs0 u=%d dp[0]=%lld dp[1]=%lld\n", u, dp[u][0], dp[u][1]);
  }
  ll ans;
  void DfsRoot(const int u, const int pre, const ll pre0, const ll pre1) {
    if (pre != -1) {
      ans = min(ans, pre0);
    }
    vector<vector<ll>> child(2, vector<ll>(2, INT64_MAX2));  // 保留最小的 2 个值

    auto Add = [](vector<ll>& child, ll v) {
      if (child.back() <= v) return;
      child.back() = v;
      if (child[0] > child[1]) {
        swap(child[0], child[1]);
      }
    };
    Add(child[0], pre0);
    Add(child[1], pre1);
    const int uv = values[u];
    Add(child[uv], 0);  // 自身
    for (auto& node : g[u]) {
      if (node.v == pre) continue;
      int v = node.v;
      ll c = node.c;
      ll v0 = min(dp[v][uv] + c, INT64_MAX2);
      ll v1 = min(dp[v][1 ^ uv] + c, INT64_MAX2);
      Add(child[0], v0);
      Add(child[1], v1);
    }

    MyPrintf("DfsRoot u=%d values=%d child[0]=%lld,%lld child[1]=%lld,%lld\n", u, values[u], child[0][0], child[0][1],
             child[1][0], child[1][1]);

    for (auto& node : g[u]) {
      if (node.v == pre) continue;
      int v = node.v;
      ll c = node.c;
      const int vv = values[v];
      ll v0 = min(dp[v][uv] + c, INT64_MAX2);
      ll v1 = min(dp[v][1 ^ uv] + c, INT64_MAX2);
      ll uPre[2] = {child[0][0], child[1][0]};
      if (uPre[0] == v0) uPre[0] = child[0][1];
      if (uPre[1] == v1) uPre[1] = child[1][1];
      MyPrintf("DfsRoot u=%d v=%d c=%lld values=%d uPre[0]=%lld uPre[1]=%lld\n", u, v, c, vv, uPre[0], uPre[1]);
      if (vv == 0) {
        DfsRoot(v, u, uPre[0] + c, uPre[1] + c);
      } else {
        DfsRoot(v, u, uPre[1] + c, uPre[0] + c);
      }
    }
  }

 public:
  int minActivationCost(vector<vector<int>>& edges, vector<int>& values_) {
    values.swap(values_);
    int n = values.size();
    for (int i = 0; i < n; i++) {
      values[i] = __builtin_popcount(values[i]) & 1;
      MyPrintf("values[%d]=%d\n", i, values[i]);
    }
    g.resize(n);
    for (auto& e : edges) {
      ll u = e[0];
      ll v = e[1];
      ll c = e[2];
      g[u].push_back({v, c});
      g[v].push_back({u, c});
    }
    dp.resize(n, vector<ll>(2, INT64_MAX2));
    Dfs0(0, -1);
    ans = INT64_MAX2;
    DfsRoot(0, -1, INT64_MAX2, INT64_MAX2);
    if (ans == INT64_MAX2) {
      ans = -1;
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