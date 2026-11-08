
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
  vector<vector<int>> g;
  string colors;
  ll ans = 0;
  vector<ll> childCnt;
  vector<ll> allBlueCost;
  vector<ll> rootRedCost;  // 子树根为红色的最小代价
  void Dfs(int u, int pre) {
    childCnt[u] = 1;
    allBlueCost[u] = 0;
    for (int v : g[u]) {
      if (v == pre) {
        continue;
      }
      Dfs(v, u);
      childCnt[u] += childCnt[v];
      allBlueCost[u] += allBlueCost[v];
    }
    if (colors[u] == 'R') {
      allBlueCost[u] += childCnt[u];
    }
  }

  // preCost 子树外都是蓝色的代价
  void DfsBlueRed(int u, int pre) {
    rootRedCost[u] = 0;
    if (colors[u] == 'B') {
      rootRedCost[u] += childCnt[u];
    }
    for (int v : g[u]) {
      if (v == pre) {
        continue;
      }
      DfsBlueRed(v, u);
      // 子树可以选择全部蓝色，也可以选择子树根是红色，取最小代价
      rootRedCost[u] += min(allBlueCost[v], rootRedCost[v]);
    }
    ans = min(ans, rootRedCost[u] + allBlueCost[0] - allBlueCost[u]);
  }

 public:
  ll minCost(int n, string colors_, vector<vector<int>>& edges) {
    g.resize(n);
    swap(colors, colors_);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    childCnt.resize(n, 0);
    allBlueCost.resize(n, 0);
    rootRedCost.resize(n, 0);
    Dfs(0, -1);
    ans = allBlueCost[0];
    DfsBlueRed(0, -1);
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