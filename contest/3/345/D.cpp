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
      fa[i] = i, score[i] = 0;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (score[x] > score[y]) {
        fa[y] = x;
      } else {
        fa[x] = y;
        if (score[x] == score[y]) {
          ++score[y];
        }
      }
    }
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
  int countCompleteComponents(int n, vector<vector<int>>& edges) {
    dsu.Init(n);
    for (auto& v : edges) {
      int x = v[0], y = v[1];
      dsu.Union(x, y);
    }

    vector<int> group(n, 0);
    vector<int> flag(n, 0);
    for (int i = 0; i < n; i++) {
      int p = dsu.Find(i);
      group[p]++;
    }

    for (auto& v : edges) {
      int x = v[0], y = v[1];
      int p = dsu.Find(x);
      flag[p]++;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (group[i] == 0) continue;
      int e = flag[i];
      int k = group[i];
      if (k * (k - 1) / 2 == e) {
        ans++;
      }
    }
    return ans;
  }
};