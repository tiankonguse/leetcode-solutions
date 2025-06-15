const int maxn = 100005;
const int maxn_log = 20;
vector<int> g[maxn];  // 需要主动初始化
ll f[maxn][maxn_log], dep[maxn];

void DfsRMQ(int u) {
  for (int v : g[u]) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    dep[v] = dep[u] + 1;
    f[v][0] = u;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点。
    for (int i = 1; i < maxn_log; i++) {
      f[v][i] = f[f[v][i - 1]][i - 1];
    }
    DfsRMQ(v);
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

int PathSum(int u, int v) {
  int lca = Lca(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
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