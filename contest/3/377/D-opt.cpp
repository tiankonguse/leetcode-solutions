// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
constexpr ll INFL = __LONG_LONG_MAX__;

ll pow29[1010] = {1};
ll pown = 1;

const int POW_BASE = 29;
inline ll Hash(const ll pre, const char c) {
  ll v = c - 'a' + 1;
  return (pre * POW_BASE + v) % mod;
}

inline ll Hash(const string& str) {
  ll pre = 0;
  for (auto c : str) {
    pre = Hash(pre, c);
  }
  return pre;
}
ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}

unordered_map<ll, int> H;
ll originalH[222], changedH[222];
ll mp[222][222];
ll preOriginalHash[1010];
ll preChangedHash[1010];
ll dp[1010];
pair<ll, int> g[222][222];
int gn[222];
int vis[222];
int inQue[222];

ll RangeHash(int l, int r, ll* preHash) {
  l--;  //(l, r]
  const int lr = r - l;
  ll R = preHash[r];
  ll L = preHash[l] * pow29[lr] % mod;
  return (R - L + mod) % mod;
}

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
set<int> replaceLen;

void Dijkstra(const int u, const int n, ll* dis) {
  memset(vis, 0, sizeof(vis));
  memset(inQue, 0, sizeof(inQue));
  que.push({0, u});
  dis[u] = 0;
  inQue[u] = 1;
  // printf("start u=%d\n", u);
  while (!que.empty()) {
    auto [fromCost, from] = que.top();
    que.pop();
    if (vis[from]) continue;
    vis[from] = 1;
    // printf("vis from=%d\n", from);
    for (int i = 0; i < gn[from]; i++) {
      auto [toCost, to] = g[from][i];
      // printf("from=%d dis[from]=%lld to=%d dis[to]=%lld toCost=%lld
      // newCost=%lld", from,dis[from],to, dis[to], toCost, dis[from] + toCost
      // );
      if (dis[from] + toCost < dis[to]) {
        dis[to] = dis[from] + toCost;
        que.push({dis[to], to});
        inQue[to] = 1;
      } else {
        if ((!inQue[to]) && dis[to] < inf) {
          que.push({dis[to], to});
          inQue[to] = 1;
        }
      }
    }
  }
}

class Solution {
  ll Dfs(const int n) {
    if (dp[n] != INFL) return dp[n];  // 无解

    if (source[n - 1] == target[n - 1]) {
      if (Dfs(n - 1) != -1) {
        dp[n] = min(dp[n], dp[n - 1]);
      }
    }

    for (const int len : replaceLen) {
      if (len > n) break;
      const int j = n - len + 1;

      // for (int j = 1; j <= n; j++) {
      Dfs(j - 1);
      if (dp[j - 1] == -1) continue;

      const ll u = RangeHash(j, n, preOriginalHash);
      const ll v = RangeHash(j, n, preChangedHash);
      if (u == v) {  // 不需要替换
        dp[n] = min(dp[n], dp[j - 1]);
        continue;
      }

      // 需要替换，先检查目标是否存在
      if (!H.count(u) || !H.count(v)) {
        continue;  // 不存在替换
      }

      const int hu = H[u];
      const int hv = H[v];
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

  string source;
  string target;

 public:
  ll minimumCost(string& source_, string& target_, vector<string>& original,
                 vector<string>& changed, vector<int>& cost) {
    source_.swap(source);
    target_.swap(target);
    while (pown <= 1000) {
      pow29[pown] = qpow(POW_BASE, pown, mod);
      pown++;
    }

    const int m = cost.size();

    H.clear();
    replaceLen.clear();
    for (int i = 0; i < m; i++) {
      auto& v = original[i];
      replaceLen.insert(v.size());
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

    memset(gn, 0, sizeof(gn));
    for (int i = 0; i < maxChar; i++) {
      for (int j = 0; j < maxChar; j++) {
        if (mp[i][j] != inf) {
          g[i][gn[i]] = {mp[i][j], j};
          gn[i]++;
          // printf("add edge: u=%d v=%d cost=%lld\n", i, j, mp[i][j]);
        }
      }
    }
    for (int i = 0; i < maxChar; i++) {
      Dijkstra(i, maxChar, mp[i]);
    }
    // for (int i = 0; i < maxChar; i++) {
    //   for (int j = 0; j < maxChar; j++) {
    //     // printf("from=%d to=%d cost=%lld\n", i, j, mp[i][j]);
    //   }
    // }

    const int n = source.size();
    preOriginalHash[0] = 0;
    preChangedHash[0] = 0;
    for (int i = 1; i <= n; i++) {
      preOriginalHash[i] = Hash(preOriginalHash[i - 1], source[i - 1]);
      preChangedHash[i] = Hash(preChangedHash[i - 1], target[i - 1]);
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
      dp[i] = INFL;
    }
    // printf("begin dfs\n");
    return Dfs(n);
  }
};