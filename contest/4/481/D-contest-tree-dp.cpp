
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
  vector<vector<int>> g;
  vector<int> group;
  vector<vector<pair<int, ll>>> gg;  // <cnt, sum>
  void DfsInit(int u, int p) {
    gg[group[u]][u] = {1, 0};
    for (int v : g[u]) {
      if (v == p) continue;
      DfsInit(v, u);
      for (int i = 0; i < 20; i++) {  // u 为根的答案
        gg[i][u].first += gg[i][v].first;
        gg[i][u].second += gg[i][v].second + gg[i][v].first;
      }
    }
    MyPrintf("u=%d g=<%d, %lld>\n", u, gg[group[u]][u].first, gg[group[u]][u].second);
  }
  ll ans;
  // pg 父节点作为子树的答案
  void DfsDp(int u, int p, vector<pair<int, ll>>& pg) {
    // 更新答案
    for (int i = 0; i < 20; i++) {  // u 为根的答案
      pg[i].second += gg[i][u].second + pg[i].first;
      pg[i].first += gg[i][u].first;
    }
    MyPrintf("u=%d pg=<%d, %lld>\n", u, pg[group[u]].first, pg[group[u]].second);
    ans += pg[group[u]].second;

    for (int v : g[u]) {
      if (v == p) continue;
      for (int i = 0; i < 20; i++) {  // u 为根不包括 v 的答案
        pg[i].first = pg[i].first - gg[i][v].first;
        pg[i].second = pg[i].second - gg[i][v].second - gg[i][v].first;
      }
      DfsDp(v, u, pg);
      for (int i = 0; i < 20; i++) {  // u 为根不包括 v 的答案
        pg[i].first = pg[i].first + gg[i][v].first;
        pg[i].second = pg[i].second + gg[i][v].second + gg[i][v].first;
      }
    }
    for (int i = 0; i < 20; i++) {  // u 为根的答案
      pg[i].first = pg[i].first - gg[i][u].first;
      pg[i].second = pg[i].second - gg[i][u].second - pg[i].first;
    }
  }

 public:
  ll interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group_) {
    g.resize(n);
    group.swap(group_);
    for (int i = 0; i < n; i++) {
      group[i]--;
    }
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    gg.resize(20, vector<pair<int, ll>>(n, {0, 0}));
    DfsInit(0, -1);
    vector<pair<int, ll>> pg(20, {0, 0});
    ans = 0;
    DfsDp(0, -1, pg);
    return ans / 2;
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