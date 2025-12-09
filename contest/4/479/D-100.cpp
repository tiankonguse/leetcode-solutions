
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
  vector<int> childsScoreSum;  // 不包含子树根，儿子分数大于0时的和
  vector<int> ans;
  int Dfs(const int u, const int p) {
    if (good[u]) {
      childsScore[u] = 1;
    } else {
      childsScore[u] = -1;
    }
    for (const auto v : g[u]) {
      if (v == p) continue;
      int ret = Dfs(v, u);
      if (ret > 0) {
        childsScore[u] += ret;
        childsScoreSum[u] += ret;
      }
    }
    return childsScore[u];
  }
  void DfsDP(const int u, const int p, const int preScore) {
    if (good[u]) {
      ans[u] = 1;
    } else {
      ans[u] = -1;
    }
    ans[u] += preScore + childsScoreSum[u];
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
    this->n = n;
    g.resize(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    childsScore.resize(n);
    childsScoreSum.resize(n, 0);
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