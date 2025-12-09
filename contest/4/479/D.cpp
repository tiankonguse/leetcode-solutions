
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
class Solution {
  int n;
  vector<vector<int>> g;
  vector<int> good;
  vector<int> childsScore;
  vector<int> ans;
  int Dfs(const int u, const int p) {
    childsScore[u] = good[u];
    for (const auto v : g[u]) {
      if (v == p) continue;
      int ret = Dfs(v, u);
      if (ret > 0) {
        childsScore[u] += ret;
      }
    }
    return childsScore[u];
  }
  void DfsDP(const int u, const int p, const int preScore) {
    ans[u] = preScore + childsScore[u];
    for (const auto v : g[u]) {
      if (v == p) continue;
      if (childsScore[v] > 0) {
        DfsDP(v, u, max(ans[u] - childsScore[v], 0));
      } else {
        DfsDP(v, u, max(ans[u], 0));
      }
    }
  }

 public:
  vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good_) {
    this->good.swap(good_);
    for (auto& v : good) {
      if (v == 0) v = -1;
    }
    this->n = n;
    g.resize(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    childsScore.resize(n);
    ans.resize(n);
    ans[0] = Dfs(0, -1);
    DfsDP(0, -1, 0);
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