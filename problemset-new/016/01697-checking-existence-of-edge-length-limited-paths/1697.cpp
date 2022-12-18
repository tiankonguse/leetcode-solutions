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
  vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList,
                                         vector<vector<int>>& queries) {
    dsu.Init(n);

    int en = edgeList.size();
    sort(edgeList.begin(), edgeList.end(),
         [](auto& a, auto& b) { return a[2] < b[2]; });

    int qn = queries.size();
    vector<pair<int, int>> qs(qn);
    for (int i = 0; i < qn; i++) {
      qs[i] = {queries[i][2], i};
    }
    sort(qs.begin(), qs.end());

    vector<bool> ans(qn, false);

    int ei = 0, qi = 0;
    while (qi < qn) {
      auto [qv, ansi] = qs[qi];
      int qa = queries[ansi][0], qb = queries[ansi][1];
      while (ei < en && edgeList[ei][2] < qv) {
        int ea = edgeList[ei][0], eb = edgeList[ei][1];
        dsu.Union(ea, eb);
        ei++;
      }
      ans[ansi] = dsu.Find(qa) == dsu.Find(qb);
      qi++;
    }

    return ans;
  }
};