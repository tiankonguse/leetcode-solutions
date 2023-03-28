// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 2000100, max6 = 2000100;

const int kind = 2, N = max5;

class TireTree {
 public:
  int tire[N][kind], word[N];
  pair<int, int> pre[N];
  int num = 0;

  void Init() {
    memset(tire[0], 0, sizeof(tire[0]));
    memset(tire[1], 0, sizeof(tire[1]));
    pre[1] = {1, 0};
    num = 2;
  }
  void Insert(const int val) {
    int p = 1;
    for (int bit = 17; bit >= 0; bit--) {
      int v = (val >> bit) & 1;
      if (!tire[p][v]) {
        memset(tire[num], 0, sizeof(tire[num]));
        word[num] = 0;
        pre[num] = {p, v};
        tire[p][v] = num++;
      }
      p = tire[p][v];
    }
    word[p] = val;
  }
  void Erase(const int val) {
    int p = 1;

    // 先找到 p 的叶子节点
    for (int bit = 17; bit >= 0; bit--) {
      int v = (val >> bit) & 1;
      p = tire[p][v];
    }

    // 逆向的删除空叶子
    word[p] = 0;
    while (p != 1 && word[p] == 0 && tire[p][0] == 0 && tire[p][1] == 0) {
      auto father = pre[p];
      tire[father.first][father.second] = 0;
      if (p + 1 == num) {
        num--;
      }
      p = father.first;
    }
  }

  int QueryMaxXor(const int val) {
    int p = 1;
    for (int bit = 17; bit >= 0; bit--) {
      int v = (val >> bit) & 1;
      int xor_v = 1 - v;

      if (tire[p][xor_v]) {
        p = tire[p][xor_v];
      } else {
        p = tire[p][v];
      }
    }
    int ans = val ^ word[p];
    // printf("val=%d p=%d word[p]=%d ans=%d\n", val, p, word[p], ans);

    return ans;
  }
};

class Solution {
  int n;

  vector<vector<int>> tree;
  unordered_map<int, vector<pair<int, int>>> query_nodes;
  vector<int> ans;
  TireTree tire_tree;

  void Dfs(int node) {
    tire_tree.Insert(node);

    if (query_nodes.count(node)) {
      for (auto& p : query_nodes[node]) {
        ans[p.first] = tire_tree.QueryMaxXor(p.second);
      }
    }
    for (auto v : tree[node]) {
      Dfs(v);
    }

    tire_tree.Erase(node);
  }

 public:
  vector<int> maxGeneticDifference(vector<int>& parents,
                                   vector<vector<int>>& queries) {
    n = parents.size();
    tree.resize(n);
    ans.resize(queries.size(), 0);

    tire_tree.Init();

    int root_pos = -1;
    for (int i = 0; i < n; i++) {
      if (parents[i] == -1) {
        root_pos = i;
      } else {
        tree[parents[i]].push_back(i);
      }
    }

    for (int i = 0; i < queries.size(); i++) {
      int node = queries[i][0];
      int val = queries[i][1];

      query_nodes[node].push_back({i, val});
    }

    Dfs(root_pos);

    return ans;
  }
};