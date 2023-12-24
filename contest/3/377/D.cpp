// #include <bits/stdc++.h>

#include "base.h"
using namespace std;


typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
constexpr ll INFL = __LONG_LONG_MAX__;

inline ll Hash(const ll pre, const char c) {
  ll v = c - 'a' + 1;
  return (pre * 29 + v) % mod;
}

inline ll Hash(const string& str) {
  ll pre = 0;
  for (auto c : str) {
    pre = Hash(pre, c);
  }
  return pre;
}

unordered_map<ll, int> H;
ll originalH[222], changedH[222];
ll mp[222][222];
ll sourceHash[1010][1010];
ll targetHash[1010][1010];
ll dp[1010];
vector<vector<pair<ll, int>>> g(222);

void floyd(int n) {  // mp[][] = inf; mp[i][i] = 0;
  for (int i = 0; i < n; i++) {
    mp[i][i] = 0;
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (i == k) continue;
      for (int j = 0; j < n; j++) {
        if (mp[i][k] + mp[k][j] < mp[i][j]) {
          mp[i][j] = mp[i][k] + mp[k][j];
        }
      }
    }
  }
}

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
min_queue<pair<ll, int>> que;

void Dijkstra(const int u, const int n, ll* dis) {
  vector<int> vis(n, 0);
  que.push({0, u});
  dis[u] = 0;
    // printf("start u=%d\n", u);
  while (!que.empty()) {
    auto [fromCost, from] = que.top();
    que.pop();
    if (vis[from]) continue;
    vis[from] = 1;
    // printf("vis from=%d\n", from);
    for (auto [toCost, to] : g[from]) {
    // printf("from=%d dis[from]=%lld to=%d dis[to]=%lld toCost=%lld newCost=%lld", from,dis[from],to, dis[to], toCost, dis[from] + toCost );
      if (dis[from] + toCost < dis[to]) {
        dis[to] = dis[from] + toCost;
      }
        if(!vis[to] && dis[to]<inf){
               que.push({dis[to], to});
          }
    }
  }
}

class Solution {
  ll Dfs(int n) {
    if (dp[n] != INFL) return dp[n];  // 无解

    for (int j = 1; j <= n; j++) {
      Dfs(j - 1);
      if (dp[j - 1] == -1) continue;

      ll u = sourceHash[j - 1][n - 1];
      ll v = targetHash[j - 1][n - 1];
      if (u == v) {  // 不需要替换
        dp[n] = min(dp[n], dp[j - 1]);
        continue;
      }

      // 需要替换，先检查目标是否存在
      if (!H.count(u) || !H.count(v)) {
        continue;  // 不存在替换
      }

      int hu = H[u];
      int hv = H[v];
      if (mp[hu][hv] == inf) {
        continue;  // 不存在替换
      }

      dp[n] = min(dp[n], dp[j - 1] + mp[hu][hv]);
    }

    if (dp[n] == INFL) {
      dp[n] = -1;
    }
    return dp[n];
  }

 public:
  ll minimumCost(const string& source, const string& target,
                 vector<string>& original, vector<string>& changed,
                 vector<int>& cost) {
    const int m = cost.size();

    g.clear();
    H.clear();
    for (int i = 0; i < m; i++) {
      auto& v = original[i];
      ll hv = Hash(v);
      int num = H.size();
      if (H.count(hv) == 0) {
          // printf("hash v=%s v=%d\n", v.c_str(), num);
        H[hv] = num;
      }
      originalH[i] = H[hv];
    }
    for (int i = 0; i < m; i++) {
      auto& v = changed[i];
      ll hv = Hash(v);

      int num = H.size();
      if (H.count(hv) == 0) {
          // printf("hash v=%s v=%d\n", v.c_str(), num);
        H[hv] = num;
      }
      changedH[i] = H[hv];
    }
    const int maxChar = H.size();
    for (int i = 0; i < maxChar; i++) {
      for (int j = 0; j < maxChar; j++) {
        mp[i][j] = inf;
      }
    }
    // printf("maxChar=%d\n", maxChar);
    for (int i = 0; i < m; i++) {
      int u = originalH[i];
      int v = changedH[i];
      ll c = cost[i];
      mp[u][v] = min(mp[u][v], c);
    }
    g.clear();
    g.resize(maxChar);
    for (int i = 0; i < maxChar; i++) {
      for (int j = 0; j < maxChar; j++) {
        if (mp[i][j] != inf) {
          g[i].push_back({mp[i][j], j});
            // printf("add edge: u=%d v=%d cost=%lld\n", i, j, mp[i][j]);
        }
      }
    }
    for (int i = 0; i < maxChar; i++) {
      Dijkstra(i, maxChar, mp[i]);
    }
    for (int i = 0; i < maxChar; i++) {
      for (int j = 0; j < maxChar; j++) {
        // printf("from=%d to=%d cost=%lld\n", i, j, mp[i][j]);
      }
    }

    const int n = source.size();
    // init sourceHash
    for (int i = 0; i < n; i++) {
      ll pre = 0;
      for (int j = i; j < n; j++) {
        pre = Hash(pre, source[j]);
        sourceHash[i][j] = sourceHash[j][i] = pre;
      }
    }

    // init targetHash
    for (int i = 0; i < n; i++) {
      ll pre = 0;
      for (int j = i; j < n; j++) {
        pre = Hash(pre, target[j]);
        targetHash[i][j] = targetHash[j][i] = pre;
      }
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
      dp[i] = INFL;
    }
    // printf("begin dfs\n");
    return Dfs(n);
  }
};