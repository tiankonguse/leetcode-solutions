// #include <bits/stdc++.h>

#include "base.h"
using namespace std;



template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
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
typedef long long ll;
class Solution {
  vector<vector<int>> matrix;
  min_queue<pair<int, int>> que;
  vector<vector<int>> ans;
  vector<vector<int>> g;
  vector<int> maxPreVal;
  int n, m;
  int K;

  int H(int x, int y) { return x * m + y; }
  pair<int, int> RH(int h){return {h / m, h % m};};
  pair<int, int> P(int x, int y) { return {matrix[x][y], dsu.Find(H(x, y))}; }
  void Add(int x0, int y0, int x1, int y1) {
    auto [av, ai] = P(x0, y0);
    auto [bv, bi] = P(x1, y1);
    if (av < bv) {
      g[ai].push_back(bi);
    } else if (av > bv) {
      g[bi].push_back(ai);
    }
  }
  void init() {
    n = matrix.size(), m = matrix.front().size();
    K = n * m;
    dsu.Init(K);
    g.resize(K);
    maxPreVal.resize(K, 0);
    ans.resize(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = j + 1; k < m; k++) {
          auto [av, ai] = P(i, j);
          auto [bv, bi] = P(i, k);
          if (av == bv) {
            dsu.Union(ai, bi);
          }
        }
      }
    }
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
          auto [av, ai] = P(i, j);
          auto [bv, bi] = P(k, j);
          if (av == bv) {
            dsu.Union(ai, bi);
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = j + 1; k < m; k++) {
          Add(i, j, i, k);
        }
      }
    }
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
          Add(i, j, k, j);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        auto [av, ai] = P(i, j);
        if (H(i, j) != ai) {
          continue;
        }
        que.push({av, ai});
        printf("i=%d j=%d av=%d ai=%d\n", i, j, av, ai);
      }
    }
  }

 public:
  vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix_) {
    matrix.swap(matrix_);
    // 相等，从上到下，从左到右
    init();
    while (!que.empty()) {
      auto [v, h] = que.top();
      que.pop();
      auto [x, y] = RH(h);
      ans[x][y] = maxPreVal[h] + 1;
      for (auto next : g[h]) {
        maxPreVal[next] = max(maxPreVal[next], maxPreVal[h] + 1);
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        auto [av, ai] = P(i, j);
        if (ans[i][j] == 0) {
          ans[i][j] = maxPreVal[ai] + 1;
        }
      }
    }
    return ans;
  }
};
