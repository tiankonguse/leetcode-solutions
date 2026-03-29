
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

typedef long long ll;

// 朴素并查集
// 参考资料：https://oi-wiki.org/ds/dsu/
// 树上并查集每个子树需要维护一个集合，保证大集合向小集合合并，并引用返回大集合就不会超时了

class Dsu {
  vector<int> fa, score, dist;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    dist.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = 0, dist[i] = 0;
    }
  }

  pair<int, int> Find(const int x) {
    if (fa[x] != x) {
      auto [root, faDist] = Find(fa[x]);
      fa[x] = root;
      dist[x] ^= faDist;
    }
    return {fa[x], dist[x]};
  }

  // Union，也成为了 Merge
  bool Union(int X, int Y, int w) {
    auto [x, xDist] = Find(X);
    auto [y, yDist] = Find(Y);
    if (x == y) {
      return (xDist ^ yDist) == w;
    } else {
      if (score[x] > score[y]) {
        fa[y] = x;
        dist[y] = xDist ^ yDist ^ w;
      } else {
        fa[x] = y;
        dist[x] = xDist ^ yDist ^ w;
        if (score[x] == score[y]) {
          ++score[y];
        }
      }
      return true;
    }
  }
};
class Solution {
 public:
  int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
    Dsu dsu;
    dsu.Init(n);
    int ans = 0;
    for (auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      if (dsu.Union(u, v, w)) {
        ans++;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif