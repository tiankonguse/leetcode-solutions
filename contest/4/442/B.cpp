
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
const int N = 101;
class Solution {
 public:
  int numberOfComponents(vector<vector<int>>& properties, int k) {
    int n = properties.size();
    int m = properties[0].size();
    dsu.Init(n);

    vector<vector<int>> g(n, vector<int>(N, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (properties[i][j] > 0) {
          g[i][properties[i][j]] = 1;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int count = 0;
        for (int x = 0; x < N; x++) {
          if (g[i][x] > 0 && g[j][x] > 0) {
            count++;
          }
        }
        if (count >= k) {
          dsu.Union(i, j);
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      MyPrintf("%d %d\n", i, dsu.Find(i));
      if (i == dsu.Find(i)) ans++;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif