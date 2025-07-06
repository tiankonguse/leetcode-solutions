
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
class Dsu {
  vector<int> fa;
  vector<int> rank;
  int block;

 public:
  void Init(int n) {
    fa.resize(n);
    rank.resize(n);
    block = n;
    for (int i = 0; i < n; i++) {
      fa[i] = i;
      rank[i] = 1;
    }
  }
  int Find(int p) {
    if (fa[p] != p) {
      fa[p] = Find(fa[p]);
    }
    return fa[p];
  }
  int Union(int u, int v) {
    u = Find(u);
    v = Find(v);
    if (u == v) return u;
    if (rank[u] > rank[v]) {
      swap(u, v);
    }
    block--;
    rank[v] += rank[u];
    fa[u] = v;
    return v;
  }
  int Rank(int x) {
    x = Find(x);
    return rank[x];
  }
  int Block() {  //
    return block;
  }
};
Dsu dsu;
class Solution {
 public:
  int minTime(int n, vector<vector<int>>& edges, int k) {
    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) { return a[2] > b[2]; });
    // 时间逆序判断
    dsu.Init(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1], t = e[2];
      dsu.Union(u, v);
      if (dsu.Block() < k) {
        return t;
      }
    }
    return 0;
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