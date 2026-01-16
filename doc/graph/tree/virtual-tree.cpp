/*
虚树：把一整颗大树浓缩成一颗小树，压缩掉一些不重要的节点

https://oi-wiki.org/graph/virtual-tree/


应用: 部分节点路径的某些答案

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace VirtualTree {
int maxLog = 20;
int vTimeStamp = 0;
vector<int> dfn;                           // dfs 序
vector<int> dep;                           // 深度
vector<vector<int>> g;                     // 原树
vector<vector<pair<int, int>>> vg;         // 虚树， <v, d>
vector<vector<int>> st;                    // 稀疏表
vector<int> timeSeq;                       // 版本
unordered_map<int, vector<int>> groupNum;  // 组编号

vector<int> A;
vector<pair<int, int>> flag;  // <version, keyPoint>
int flagVersion;

void BuildDfn(const int u, const int p) {
  dfn[u] = vTimeStamp;
  timeSeq[vTimeStamp] = u;
  vTimeStamp++;
  st[0][u] = p;
  for (int v : g[u]) {
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    BuildDfn(v, u);
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

void BuildGroup(int n, const vector<int>& group) {
  groupNum.clear();
  for (int t = 0; t < n; t++) {  // 继续 dfs 序构建分组的关键点
    int u = timeSeq[t];
    int id = group[u];
    groupNum[id].push_back(u);
  }
}
void InitVirtualTree(int n, const vector<vector<int>>& edges, const vector<int>& group) {
  g.clear();
  g.resize(n);
  for (auto& e : edges) {
    int u = e[0], v = e[1];
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfn.clear();
  dfn.resize(n);
  dep.clear();
  dep.resize(n);
  timeSeq.clear();
  timeSeq.resize(n);
  vTimeStamp = 0;
  maxLog = log2(n) + 1;
  st.clear();
  st.resize(maxLog, vector<int>(n));

  dep[0] = 0;
  BuildDfn(0, -1);
  BuildSparseTable(n);
  BuildGroup(n, group);

  A.clear();
  A.reserve(n);
  flag.clear();
  flag.resize(n);
  flagVersion = 0;
  vg.clear();
  vg.resize(n);
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

void ResetVirtualTreeGroup() {
  // 清空虚树
  for (auto u : A) {
    vg[u].clear();
  }
  A.clear();
}

int BuildVirtualTree(int id) {
  // nodes 关键点按照 dfs 序排序
  const vector<int>& nodes = groupNum[id];
  flagVersion++;

  ResetVirtualTreeGroup();

  int m = nodes.size();
  auto Add = [](int u, int isKey) {
    if (flag[u].first != flagVersion) {
      flag[u] = {flagVersion, isKey};
      A.push_back(u);
    }
  };
  for (int i = 1; i < m; i++) {
    int u = nodes[i], v = nodes[i - 1];
    Add(u, 1);
    Add(v, 1);
    Add(Lca(u, v), 0);
  }
  sort(A.begin(), A.end(), [&](int u, int v) { return dfn[u] < dfn[v]; });
  m = A.size();
  for (int i = 1; i < m; i++) {
    int v = A[i - 1], u = A[i];
    int lca = Lca(u, v);
    int d = dep[u] - dep[lca];
    vg[lca].push_back({u, d});
    vg[u].push_back({lca, d});
  }
  return A.front();  // 第一个节点当做根
}

};  // namespace VirtualTree

ll ans = 0;
int Dfs(const int u, const int p, const ll allNum) {
  ll uNum = 0;
  if (VirtualTree::flag[u].second) {
    uNum = 1;
  }
  for (auto [v, d] : VirtualTree::vg[u]) {
    if (v == p) continue;
    int vNum = Dfs(v, u, allNum);
    ans += vNum * (allNum - vNum) * d;
    uNum += vNum;
  }
  return uNum;
}

ll Solver(int n, vector<vector<int>>& edges, vector<int>& group) {
  VirtualTree::InitVirtualTree(n, edges, group);

  ans = 0;
  for (auto [id, nodes] : VirtualTree::groupNum) {
    // nodes 是同一组的关键节点，已经按 dfn 排序
    int m = nodes.size();
    if (m <= 1) continue;
    int root = VirtualTree::BuildVirtualTree(id);
    Dfs(root, -1, m);
  }
  return ans;
}