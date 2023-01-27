// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

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
int maxPreVal[max6];
vector<pair<int, int>> que;

struct G {
  void Init(int n) {
    memset(next, -1, sizeof(int) * n);
    memset(to, -1, sizeof(int) * n);
    index = n;
  }
  void Add(int a, int b) {
    to[index] = b;
    next[index] = next[a];
    next[a] = index;
    index++;
  }
  int Next(int a) { return next[a]; }
  int To(int a) { return to[a]; }
  int index;
  int next[max6];
  int to[max6];
} g;

typedef long long ll;
class Solution {
  vector<vector<int>> matrix;
  vector<vector<int>> ans;
  int n, m;
  int K;

  int H(int x, int y) { return x * m + y; }
  pair<int, int> RH(int h) { return {h / m, h % m}; };
  pair<int, int> P(int x, int y) { return {matrix[x][y], dsu.Find(H(x, y))}; }
  void Add(int x0, int y0, int x1, int y1) {
    auto [av, ai] = P(x0, y0);
    auto [bv, bi] = P(x1, y1);
    if (av < bv) {
      g.Add(ai, bi);
    } else if (av > bv) {
      g.Add(bi, ai);
    }
  }

  void Row(bool eqFlag) {
    vector<pair<int, int>> tmp(m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        tmp[j] = {matrix[i][j], j};
      }
      sort(tmp.begin(), tmp.end());
      for (int j = 1; j < m; j++) {
        auto [v0, j0] = tmp[j - 1];
        auto [v1, j1] = tmp[j];
        auto [av, ai] = P(i, j0);
        auto [bv, bi] = P(i, j1);

        if (v0 == v1 && eqFlag) {
          dsu.Union(ai, bi);
        } else if (v0 != v1 && !eqFlag) {
          Add(i, j0, i, j1);
        }
      }
    }
  }
  void Col(bool eqFlag) {
    vector<pair<int, int>> tmp(n);
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) {
        tmp[i] = {matrix[i][j], i};
      }
      sort(tmp.begin(), tmp.end());
      for (int i = 1; i < n; i++) {
        auto [v0, i0] = tmp[i - 1];
        auto [v1, i1] = tmp[i];
        auto [av, ai] = P(i0, j);
        auto [bv, bi] = P(i1, j);

        if (v0 == v1 && eqFlag) {
          dsu.Union(ai, bi);
        } else if (v0 != v1 && !eqFlag) {
          Add(i0, j, i1, j);
        }
      }
    }
  }
  void init() {
    n = matrix.size(), m = matrix.front().size();
    K = n * m;
    dsu.Init(K);
    g.Init(K);
    fill(maxPreVal, maxPreVal + K, 0);
    ans.resize(n, vector<int>(m, 0));

    Row(true);
    Col(true);
    Row(false);
    Col(false);

    que.reserve(K);
    que.clear();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        auto [av, ai] = P(i, j);
        if (H(i, j) != ai) {
          continue;
        }
        que.push_back({av, ai});
        // printf("i=%d j=%d av=%d ai=%d\n", i, j, av, ai);
      }
    }
    sort(que.begin(), que.end());
  }

 public:
  vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix_) {
    matrix.swap(matrix_);
    // 相等，从上到下，从左到右
    init();
    for (auto [v, h] : que) {
      auto [x, y] = RH(h);
      ans[x][y] = maxPreVal[h] + 1;

      int a = g.Next(h);
      while (a != -1) {
        int b = g.To(a);
        maxPreVal[b] = max(maxPreVal[b], maxPreVal[h] + 1);
        a = g.Next(a);
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
