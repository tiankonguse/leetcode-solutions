
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 508 / 510 个通过的测试用例 超出输出限制

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
const int maxn = 100005;
const int maxn_log = 20;
vector<pair<int, ll>> g[maxn];
ll f[maxn][maxn_log], dep[maxn], preDis[maxn];
void Dfs(int u, int pre) {
  for (auto [v, w] : g[u]) {
    if (v == pre) continue;
    preDis[v] = preDis[u] + w;
    Dfs(v, u);
  }
}
void DfsRMQ(int u, int pre) {
  for (auto [v, w] : g[u]) {
    if (v == pre) continue;
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    dep[v] = dep[u] + 1;
    f[v][0] = u;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点。
    for (int i = 1; i < maxn_log; i++) {
      f[v][i] = f[f[v][i - 1]][i - 1];
    }
    DfsRMQ(v, u);
  }
}

int Lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int d = dep[u] - dep[v], i = maxn_log - 1; d && i >= 0; i--) {
    if (d & (1 << i)) {
      u = f[u][i];
      d = d ^ (1 << i);
    }
  }
  if (u == v) return u;
  for (int i = maxn_log - 1; i >= 0; i--) {
    if (f[u][i] != f[v][i]) {
      u = f[u][i];
      v = f[v][i];
    }
  }
  return f[u][0];
}
class Solution {
  // 求 u 到 pre 路径上的一个点 p，使得路径和 dis(u,p) 满足 checkCallback
  int SolverU(const int u, const int pre, function<int(ll)> checkCallback) {
    int l = 0, r = dep[u] - dep[pre];
    MyPrintf("u = %d, pre = %d, l = %d, r = %d\n", u, pre, l, r);
    while (l < r) {
      int mid = (l + r) / 2;
      // 在 RMQ 中找到 u 的第 mid 个祖先
      int p = u;
      int d = mid;
      for (int i = maxn_log - 1; d && i >= 0; i--) {
        if (d & (1 << i)) {
          p = f[p][i];
          d = d ^ (1 << i);
        }
      }
      ll sum = preDis[u] - preDis[p];
      MyPrintf("search: u = %d, pre = %d, l = %d, r = %d, mid=%d  p = %d sum=%lld\n", u, pre, l, r, mid, p, sum);
      if (checkCallback(sum)) {  // 满足条件，说明 p 是一个候选答案，但是还有更小的
        MyPrintf("checkCallback true sum = %lld\n", sum);
        r = mid;
      } else {  // 不满足条件，说明 p 不是一个候选答案，但是还有更大的
        MyPrintf("checkCallback false sum = %lld\n", sum);
        l = mid + 1;
      }
    }
    int p = u;
    int d = r;
    for (int i = maxn_log - 1; d && i >= 0; i--) {
      if (d & (1 << i)) {
        p = f[p][i];
        d = d ^ (1 << i);
      }
    }

    MyPrintf("u = %d, pre = %d, l = %d, r = %d, p = %d\n", u, pre, l, r, p);
    return p;
  }

  // 求 u 到 pre 路径上的一个点 p，使得路径和 dis(u,p) 满足 checkCallback
  int SolverV(const int u, const int pre, function<int(ll)> checkCallback) {
    int l = 0, r = dep[u] - dep[pre];
    MyPrintf("u = %d, pre = %d, l = %d, r = %d\n", u, pre, l, r);
    while (l < r) {
      int mid = (l + r) / 2;
      // 在 RMQ 中找到 u 的第 mid 个祖先
      int p = u;
      int d = mid;
      for (int i = maxn_log - 1; d && i >= 0; i--) {
        if (d & (1 << i)) {
          p = f[p][i];
          d = d ^ (1 << i);
        }
      }
      ll sum = preDis[u] - preDis[p];
      MyPrintf("search: u = %d, pre = %d, l = %d, r = %d, mid=%d  p = %d sum=%lld\n", u, pre, l, r, mid, p, sum);
      if (checkCallback(sum)) {  // 满足条件，说明 p 是一个候选答案，但是还有更小的
        MyPrintf("checkCallback true sum = %lld\n", sum);
        l = mid + 1;
      } else {  // 不满足条件，说明 p 不是一个候选答案，但是还有更大的
        MyPrintf("checkCallback false sum = %lld\n", sum);
        r = mid;
      }
    }
    int p = u;
    int d = r - 1;
    for (int i = maxn_log - 1; d && i >= 0; i--) {
      if (d & (1 << i)) {
        p = f[p][i];
        d = d ^ (1 << i);
      }
    }

    MyPrintf("u = %d, pre = %d, l = %d, r = %d, p = %d\n", u, pre, l, r, p);
    return p;
  }

 public:
  vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
    for (int i = 0; i < n; i++) {
      g[i].clear();
    }
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      ll w = e[2];
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    preDis[0] = 0;
    Dfs(0, -1);
    DfsRMQ(0, -1);
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int u = q[0], v = q[1];
      if (u == v) {
        ans.push_back(u);
        continue;
      }
      int lca = Lca(u, v);
      ll dis = preDis[u] + preDis[v] - 2 * preDis[lca];
      ll uhalf = (dis + 1) / 2;
      ll vhalf = dis - uhalf;
      // u -> v
      if (lca == u) {  // u 是 v 的祖先
        ans.push_back(SolverV(v, lca, [&vhalf](ll sum) { return sum <= vhalf; }));
      } else if (lca == v) {  // v 是 u 的祖先
        ans.push_back(SolverU(u, lca, [&uhalf](ll sum) { return sum >= uhalf; }));
      } else {  // u 和 v 之间有一个公共祖先
        ll disu = preDis[u] - preDis[lca];
        if (disu >= uhalf) {
          ans.push_back(SolverU(u, lca, [&uhalf](ll sum) { return sum >= uhalf; }));
        } else {
          ll other = uhalf - disu;
          MyPrintf("u = %d, v = %d, lca = %d, dis = %lld, uhalf = %lld, vhalf = %lld, disu = %lld\n", u, v, lca, dis,
                   uhalf, vhalf, disu);
          ans.push_back(SolverV(v, lca, [&vhalf](ll sum) { return sum <= vhalf; }));
        }
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