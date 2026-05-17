
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 986 / 999 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
void floyd(int n, vector<vector<ll>>& g) {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (i == k) continue;
      for (size_t j = 0; j < n; j++) {
        ll tmp = g[i][k] + g[k][j];
        if (tmp < g[i][j]) {
          g[i][j] = tmp;
        }
      }
    }
  }
}
class Solution {
 public:
  vector<int> minCost(int n, vector<int>& prices, vector<vector<int>>& roads) {
    vector<vector<ll>> g(n, vector<ll>(n, 1e18));
    vector<vector<ll>> rg(n, vector<ll>(n, 1e18));
    for (auto& r : roads) {
      ll u = r[0], v = r[1], c = r[2], t = r[3];
      g[u][v] = min(g[u][v], c);
      g[v][u] = min(g[v][u], c);
      rg[u][v] = min(rg[u][v], c * t);
      rg[v][u] = min(rg[v][u], c * t);
    }
    for (int i = 0; i < n; i++) {
      g[i][i] = 0;
      rg[i][i] = 0;
    }
    floyd(n, g);
    floyd(n, rg);
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      ans[i] = prices[i];
      for (int j = 0; j < n; j++) {
        ans[i] = min(ans[i], int(prices[j] + g[i][j] + rg[i][j]));
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