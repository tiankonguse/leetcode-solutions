
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
  vector<int> fa, score;
  int block;

 public:
  void Init(int n) {
    block = n;
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
      block--;
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
  int GetBlock() { return block; }
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
  int maxStability(const int n, vector<vector<int>>& edges, const int k) {
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) { return a[2] > b[2]; });
    auto Check = [&](const int minVal) -> bool {
      dsu.Init(n);
      for (auto& e : edges) {
        int u = e[0], v = e[1], s = e[2], m = e[3];
        if (m == 0) continue;
        // 必须加入到生成树中
        if (s < minVal) {
          return false;
        }
        if (dsu.Find(u) == dsu.Find(v)) {
          return false;  // 形成环
        }
        dsu.Union(u, v);
      }
      if (dsu.GetBlock() == 1) return true;
      int K = k;
      for (auto& e : edges) {
        int u = e[0], v = e[1], s = e[2], m = e[3];
        if (m == 1) continue;
        if (dsu.Find(u) == dsu.Find(v)) continue;
        if (s >= minVal) {
          dsu.Union(u, v);
        } else if (K > 0 && s * 2 >= minVal) {
          dsu.Union(u, v);
          K--;
        }
        if (dsu.GetBlock() == 1) return true;
      }
      return false;
    };
    if (!Check(1)) {
      return -1;
    }
    int l = 1, r = 1e5+10;
    while (l < r) {
      int mid = (l + r) / 2;
      if (Check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
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