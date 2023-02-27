// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  const int RED = 0, BLUE = 1;

 public:
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges,
                                       vector<vector<int>>& blueEdges) {
    vector<vector<vector<int>>> g(2, vector<vector<int>>(n));

    for (auto& v : redEdges) {
      int a = v[0], b = v[1];
      g[RED][a].push_back(b);
    }
    for (auto& v : blueEdges) {
      int a = v[0], b = v[1];
      g[BLUE][a].push_back(b);
    }

    vector<vector<int>> dp(2, vector<int>(n, INT_MAX));
    queue<pair<int, int>> que;
    que.push({0, RED});
    que.push({0, BLUE});
    dp[RED][0] = 0;
    dp[BLUE][0] = 0;

    while (!que.empty()) {
      auto [from, color] = que.front();
      que.pop();

      int nextColor = 1 - color;
      for (auto to : g[nextColor][from]) {
        if (dp[nextColor][to] != INT_MAX) continue;

        dp[nextColor][to] = dp[color][from] + 1;
        que.push({to, nextColor});
      }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      ans[i] = min(dp[RED][i], dp[BLUE][i]);
      if(ans[i] == INT_MAX){
        ans[i] = -1;
      }
    }
    return ans;
  }
};