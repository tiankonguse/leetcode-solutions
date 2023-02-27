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
  int n;
  vector<pair<int, int>> nums;
  bool Check(vector<vector<int>>& lcp) {
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (lcp[i][j] != lcp[j][i]) return false;
        if (i == j && lcp[i][j] != (n - i)) return false;
        if (lcp[i][j] > n - max(i, j)) return false;
        if (n - max(i, j) > 1 && lcp[i][j] > 0 &&
            lcp[i][j] != lcp[i + 1][j + 1] + 1)
          return false;
      }
    }
    return true;
  }
  void Build(vector<vector<int>>& lcp) {
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (lcp[i][j] == 0) continue;
        if (i > 0 && lcp[i - 1][j - 1] > 0) continue;
        nums.push_back({i, j});
      }
    }
  }

 public:
  string findTheString(vector<vector<int>>& lcp) {
    n = lcp.size();
    if (!Check(lcp)) {
      return "";
    }

    dsu.Init(n);

    Build(lcp);

    for (auto [i, j] : nums) {
      for (int k = 0; k < lcp[i][j]; k++) {
        dsu.Union(i + k, j + k);
      }
    }

    // check union
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int num = lcp[i][j];
        if (j + num < n && dsu.Find(i + num) == dsu.Find(j + num)) {
          return "";
        }
      }
    }

    // build ans
    string ans;
    ans.resize(n, '0');
    int index = 0;
    for (int i = 0; i < n; i++) {
      int pre = dsu.Find(i);
      if (ans[pre] == '0') {
        if (index >= 26) return "";
        ans[pre] = 'a' + index;
        index++;
      }
      ans[i] = ans[pre];
    }
    return ans;
  }
};