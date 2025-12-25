/*
最近公共祖先简称 LCA（Lowest Common Ancestor）。
两个节点的最近公共祖先，就是这两个点的公共祖先里面，离根最远的那个。
记某点集 𝑆 ={𝑣1,𝑣2,…,𝑣𝑛} 的最近公共祖先为 LCA(𝑣1,𝑣2,…,𝑣𝑛) 或 LCA(𝑆) 

性质：

1. LCA({u}) = u
2. u 是 v 的祖先，那么 LCA({u, v}) = u
3. u和v 不是祖先关系，那么 u 和 v 处于 LCA(u,v) 的不同的子树中
4. 前序遍历中，LCA(S) 出现在所有 S 中点的前面，后序遍历中，LCA(S) 出现在所有 S 中点的后面
5. 两个点集 S1 和 S2 的 LCA(S1 U S2) = LCA(LCA(S1), LCA(S2))
6. d(u, v) = dep(u) + dep(v) - 2 * dep(LCA(u,v))，其中 d(u,v) 表示 u 和 v 的距离， dep(u) 表示 u 到根的深度


算法：

1. 朴素算法 O(N)，对齐深度，依次向上跳，判断父节点是否相同
2. 倍增算法 O(N log(N) + Q log(N))
3. Tarjan 离线算法 O(N + Q)，适用于静态树
4. 欧拉序转RMQ O(n)


https://oi-wiki.org/graph/lca/
https://wcipeg.com/wiki/Lowest_common_ancestor
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
const int maxLog = 20;
vector<int> g[maxn];  // 需要主动初始化
ll st[maxLog][maxn];  // st[i][v] 表示 v 的 2^i 祖先
int dep[maxn];

void BuildDepth(const int u, const int p) {
  st[u][0] = p;
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

int PathSum(int u, int v) {
  int lca = Lca(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
}

int Lca(int u, int v) {
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
    }
  }
  return st[0][u];
}
