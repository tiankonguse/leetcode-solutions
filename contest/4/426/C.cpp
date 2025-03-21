
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  int K;
  void Init(vector<vector<int>>& edges, int& n, vector<vector<int>>& g) {
    n = edges.size() + 1;
    g.resize(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }

  void DfsChild(int u, int pre, vector<vector<int>>& g,
                vector<vector<int>>& child) {
    vector<int>& uChild = child[u];
    for (int i = 0; i <= K; i++) {
      uChild[i] = 1;  // 小于等于 i 的个数
    }
    for (auto& v : g[u]) {
      if (v == pre) continue;
      DfsChild(v, u, g, child);
      const vector<int>& vChild = child[v];
      for (int i = 0; i <= K && vChild[i]; i++) {
        uChild[i + 1] += vChild[i];
      }
    }
  }

  void DfsAll(int u, int pre, vector<vector<int>>& g,
              vector<vector<int>>& child, vector<vector<int>>& all) {
    const vector<int>& uChild = child[u];
    vector<int>& uAll = all[u];
    for (int i = 0; i <= K && uChild[i]; i++) {
      uAll[i] = uChild[i];  // 复制子树
    }
    if (pre != -1) {
      vector<int>& preK = all[pre];
      for (int i = 0; i <= K && preK[i]; i++) {
        uAll[i + 1] += preK[i];  // 把父节点的合并上来
      }
    }

    for (auto& v : g[u]) {
      if (v == pre) continue;
      const vector<int>& vChild = child[v];
      for (int i = 0; i <= K && vChild[i]; i++) {
        uAll[i + 1] -= vChild[i];  // 删除当前子树
      }
      DfsAll(v, u, g, child, all);
      for (int i = 0; i <= K && vChild[i]; i++) {
        uAll[i + 1] += vChild[i];  // 恢复当前子树
      }
    }
  }

 public:
  vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                             vector<vector<int>>& edges2, const int k) {
    K = k;
    vector<vector<int>> g1, g2;
    int n1, n2;
    vector<vector<int>> child1, child2;
    vector<vector<int>> all1, all2;
    Init(edges1, n1, g1);
    child1.resize(n1, vector<int>(K + 2, 0));
    all1.resize(n1, vector<int>(K + 2, 0));

    Init(edges2, n2, g2);
    child2.resize(n2, vector<int>(K + 2, 0));
    all2.resize(n2, vector<int>(K + 2, 0));

    DfsChild(0, -1, g1, child1);
    DfsAll(0, -1, g1, child1, all1);
    DfsChild(0, -1, g2, child2);
    DfsAll(0, -1, g2, child2, all2);

    vector<int> ans(n1, 0);
    for (int i = 0; i < n1; i++) {
      ans[i] = all1[i][K];
      for (int j = 0; k > 0 && j < n2; j++) {
        ans[i] = max(ans[i], all1[i][k] + all2[j][k - 1]);
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>> edges1, vector<vector<int>> edges2, int k,
          vector<int> ans) {
  TEST_SMP3(Solution, maxTargetNodes, ans, edges1, edges2, k);
}

int main() {
  vector<vector<int>> edges1;
  vector<vector<int>> edges2;
  int k;
  vector<int> ans;

  edges1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
  edges2 = {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}};
  k = 2;
  ans = {9, 7, 9, 8, 8};
  Test(edges1, edges2, k, ans);

  edges1 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}};
  edges2 = {{0, 1}, {1, 2}, {2, 3}};
  k = 1;
  ans = {6, 3, 3, 3, 3};
  Test(edges1, edges2, k, ans);
  return 0;
}

#endif
