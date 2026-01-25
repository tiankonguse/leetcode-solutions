
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
const int maxn = 100005;
const int maxn_log = 20;
vector<int> g[maxn];  // 需要主动初始化
ll f[maxn][maxn_log], dep[maxn];

void DfsRMQ(int u, int p) {
  for (int v : g[u]) {
    if (v == p) continue;
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

// u 向上跳 k 步，返回跳到的节点编号
int PreKthAncestor(int u, int k) {
  for (int i = maxn_log - 1; k && i >= 0; i--) {
    if (k & (1 << i)) {
      u = f[u][i];
      k = k ^ (1 << i);
    }
  }
  return u;
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

int PathSum(int u, int v) {
  int lca = Lca(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
}
void Init(int n) {
  for (int i = 0; i < n; i++) {
    g[i].clear();
    dep[i] = 0;
    for (int j = 0; j < maxn_log; j++) {
      f[i][j] = 0;
    }
  }
}
class Solution {
  bool Check(ll xi, ll yi, ll zi) {
    // 判断是否满足勾股定理
    ll nums[3] = {xi, yi, zi};
    sort(nums, nums + 3);
    return nums[0] * nums[0] + nums[1] * nums[1] == nums[2] * nums[2];
  }

 public:
  int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {
    Init(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    DfsRMQ(0, -1);

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ll xi = PathSum(i, x);
      ll yi = PathSum(i, y);
      ll zi = PathSum(i, z);
      MyPrintf("i=%d, xi=%lld, yi=%lld, zi=%lld\n", i, xi, yi, zi);
      if (Check(xi, yi, zi)) {
        ans++;
      }
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(int n, const vector<vector<int>>& edges, int x, int y, int z, const int& ans) {
  TEST_SMP5(Solution, specialNodes, ans, n, edges, x, y, z);
}

int main() {
  {
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}};
    Test(4, edges, 1, 2, 3, 3);
  }
  return 0;
}

#endif