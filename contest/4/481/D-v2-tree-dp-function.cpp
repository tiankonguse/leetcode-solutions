
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
    gg[u][group[u]] = {1, 0};
    for (int v : g[u]) {
      if (v == p) continue;
      DfsInit(v, u);
      for (int i = 0; i < 20; i++) {  // u 为根的答案
        const auto [vCnt, vSum] = gg[v][i];
        auto& [uCnt, uSum] = gg[u][i];
        uCnt += vCnt;
        uSum += vSum + vCnt;
      }
    }
  }
  ll ans;
  void AddChild(vector<pair<int, ll>>& ug, const vector<pair<int, ll>>& vg) {
    for (int i = 0; i < 20; i++) {  // u 为根，排除包括 v 的答案
      const auto [vCnt, vSum] = vg[i];
      auto& [ugCnt, ugSum] = ug[i];
      ugCnt = ugCnt + vCnt;
      ugSum = ugSum + vSum + vCnt;
    }
  }
  void RemoveChild(vector<pair<int, ll>>& ug, const vector<pair<int, ll>>& vg) {
    for (int i = 0; i < 20; i++) {  // u 为根，排除包括 v 的答案
      const auto [vCnt, vSum] = vg[i];
      auto& [ugCnt, ugSum] = ug[i];
      ugCnt = ugCnt - vCnt;
      ugSum = ugSum - vSum - vCnt;
    }
  }
  // pg 父节点作为子树的答案
  void DfsDp(int u, int p, const vector<pair<int, ll>>& pg) {
    // 更新答案
    AddChild(gg[u], pg);
    ans += gg[u][group[u]].second;  // 计算 u 为根的答案
    for (int v : g[u]) {
      if (v == p) continue;
      RemoveChild(gg[u], gg[v]);
      DfsDp(v, u, gg[u]);
      AddChild(gg[u], gg[v]);
    }
    RemoveChild(gg[u], pg);
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
    gg.resize(n, vector<pair<int, ll>>(20, {0, 0}));
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

#endif©leetcode