
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
  int Dfs(const int u, const int p, const int id, const ll allNum) {
    ll uNum = 0;
    if (group[u] == id) uNum++;
    for (int v : g[u]) {
      if (v == p) continue;
      int vNum = Dfs(v, u, id, allNum);
      ans += vNum * (allNum - vNum);
      uNum += vNum;
    }
    return uNum;
  }

  unordered_map<int, ll> groupNum;
  ll ans = 0;

 public:
  ll interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group_) {
    g.resize(n);
    group.swap(group_);
    for (auto v : group) {
      groupNum[v]++;
    }
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    ans = 0;
    for (auto [id, num] : groupNum) {
      Dfs(0, -1, id, num);
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