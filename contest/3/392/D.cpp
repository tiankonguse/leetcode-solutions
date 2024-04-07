// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 朴素并查集
// 参考资料：https://oi-wiki.org/ds/dsu/
// 树上并查集每个子树需要维护一个集合，保证大集合向小集合合并，并引用返回大集合就不会超时了

class Dsu {
  vector<int> fa, score;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = -1;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y, int v) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (score[x] == -1) {
        score[x] = v;
      }
      if (score[y] == -1) {
        score[y] = v;
      }
      fa[y] = x;
    }
    score[x] = score[y] = score[x] & score[y] & v;
  }
  void AddScore(int x) {
    x = Find(x);
    score[x]++;
  }

  int GetScore(int x) {
    x = Find(x);
    return score[x];
  }
};
Dsu dsu;
class Solution {
 public:
  vector<int> minimumCost(int n, vector<vector<int>>& edges,
                          vector<vector<int>>& query) {
    dsu.Init(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1], w = e[2];
      dsu.Union(u, v, w);
    }
    vector<int> ans;
    ans.reserve(query.size());
    for (auto& q : query) {
      int u = q[0], v = q[1];
      if(u == v){
        ans.push_back(0);
        continue;
      }
      u = dsu.Find(u);
      v = dsu.Find(v);
      if (u != v) {
        ans.push_back(-1);
      } else {
        ans.push_back(dsu.GetScore(v));
      }
    }
    return ans;
  }
};