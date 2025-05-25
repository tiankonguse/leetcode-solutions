
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
int dp[161][161][2];
int dpChild[161][161][161][2];
class Solution {
  vector<int> present;
  vector<int> future;
  vector<vector<int>> g;  // 有向树
  vector<vector<int>> G;  // 无向树
  void InitTree(int u, int pre) {
    for (auto v : g[u]) {
      if (v == pre) continue;
      G[u].push_back(v);
      InitTree(v, u);
    }
  }
  int DfsChild(const int u, const int preFlag, const int m, const int B) {  //
    if (m <= 0) return 0;

    int& ret = dpChild[u][B][m][preFlag];
    if (ret != -1) return ret;
    ret = 0;

    // 最后一个儿子所在子树给多少钱
    const int v = G[u][m - 1];
    for (int b = 0; b <= B; b++) {
      int tmp = DfsChild(u, preFlag, m - 1, B - b) + Dfs(v, preFlag, b);
      ret = max(ret, tmp);
    }

    return ret;
  }
  int Dfs(const int u, const int preFlag, const int B) {
    int& ret = dp[u][B][preFlag];
    if (ret != -1) return ret;
    ret = 0;

    // 不选择
    ret = DfsChild(u, 0, G[u].size(), B);

    // 选择
    int buy = present[u];
    if (preFlag) {
      buy = present[u] / 2;
    }
    if (buy <= B) {  // 能买才买
      int tmp = future[u] - buy + DfsChild(u, 1, G[u].size(), B - buy);
      ret = max(ret, tmp);
    }

    return ret;
  };

 public:
  int maxProfit(int n, vector<int>& present_, vector<int>& future_, vector<vector<int>>& hierarchy, int budget) {
    future.swap(future_);
    present.swap(present_);
    g.resize(n);
    G.resize(n);
    for (auto& v : hierarchy) {
      int a = v[0] - 1, b = v[1] - 1;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    InitTree(0, -1);
    memset(dp, -1, sizeof(dp));
    memset(dpChild, -1, sizeof(dpChild));

    return Dfs(0, 0, budget);
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