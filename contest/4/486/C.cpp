
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
const int maxLog = 20;
vector<int> g[maxn];  // 需要主动初始化
ll st[maxLog][maxn];  // st[i][v] 表示 v 的 2^i 祖先
int dep[maxn];

void Init(int n) {
  for (int i = 0; i < n; i++) {
    g[i].clear();
    dep[i] = 0;
  }
}

void BuildDepth(const int u, const int p) {
  st[0][u] = p;
  for (int v : g[u]) {
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    BuildDepth(v, u);
  }
}

void BuildSparseTable(int n) {
  for (int i = 1; i < maxLog; i++) {
    for (int v = 0; v < n; v++) {
      int p = st[i - 1][v];
      if (p != -1) {
        st[i][v] = st[i - 1][p];
      } else {
        st[i][v] = -1;
      }
    }
  }
}

// u 向上跳 k 步，返回跳到的节点编号
int PreKthAncestor(int u, int k) {
  for (int i = maxLog - 1; k && i >= 0; i--) {
    if (k & (1 << i)) {
      assert(u != -1);
      u = st[i][u];
      k = k ^ (1 << i);
    }
  }
  return u;
}

int UptoDep(int u, int d) {
  if (dep[u] <= d) {
    return u;
  }
  return PreKthAncestor(u, dep[u] - d);
}

int Lca(int u, int v) {
  MyPrintf("u=%d, v=%d pre[u]=%lld pre[v]=%lld\n", u, v, st[0][u], st[0][v]);
  if (dep[u] < dep[v]) {
    swap(u, v);
  }
  u = UptoDep(u, dep[v]);
  if (u == v) {
    return u;
  }
  for (int i = maxLog - 1; i >= 0; i--) {
    if (st[i][u] != st[i][v]) {
      u = st[i][u];
      v = st[i][v];
      MyPrintf("i=%d, u=%d, v=%d\n", i, u, v);
    }
  }
  return st[0][u];
}

int PathSum(int u, int v) {
  int lca = Lca(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
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
    BuildDepth(0, -1);
    BuildSparseTable(n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ll xi = PathSum(i, x);
      ll yi = PathSum(i, y);
      ll zi = PathSum(i, z);
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
  // {
  //   vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}};
  //   Test(4, edges, 1, 2, 3, 3);
  // }
  {
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}};
    Test(4, edges, 0, 3, 2, 0);
  }
  return 0;
}

#endif