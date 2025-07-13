
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
  int N;
  vector<vector<vector<int>>> dp;
  vector<vector<int>> g;
  string label;
  int n;
  int Dfs(int u, int v, const int mask) {
    int& ret = dp[u][v][mask];
    if (ret != -1) return ret;
    ret = 0;
    if (g[u][v]) ret = 2;
    for (int i = 0; i < n; i++) {
      if (g[u][i] && g[i][v] && (mask & (1 << i))) {
        ret = 3;
      }
    }
    for (int i = 0; i < n; i++) {
      if (!(mask & (1 << i))) continue;
      if (!g[u][i]) continue;
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        if (!(mask & (1 << j))) continue;
        if (!g[v][j]) continue;
        if (label[i] != label[j]) continue;
        ret = max(ret, 2 + Dfs(i, j, mask ^ (1 << i) ^ (1 << j)));
      }
    }
    return ret;
  }

 public:
  int maxLen(int n, vector<vector<int>>& edges, string label_) {
    this->n = n;
    label.swap(label_);
    N = 1 << n;
    g.resize(n, vector<int>(n, 0));
    dp.resize(n, vector(n, vector(N + 1, -1)));
    for (auto& e : edges) {
      g[e[0]][e[1]] = 1;
      g[e[1]][e[0]] = 1;
    }
    int ans = 1;
    int MASK = (1 << n) - 1;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (label[i] != label[j]) continue;
        ans = max(ans, Dfs(i, j, MASK ^ (1 << i) ^ (1 << j)));
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