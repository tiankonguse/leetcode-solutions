// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

/*
580 / 583 个通过的测试用例 超出时间限制
*/

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max6];
ll qpowCache[max6];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

ll hash(const char* str, int l, int r) {
  ll pre = 0;
  for (int i = l; i < r; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
  }
  return pre;
}

void Init(const char* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
    h[i] = pre;
  }
}
class Solution {
  vector<vector<ll>> g;
  string str;
  string S;
  vector<bool> ans;
  vector<pair<ll, ll>> ranges;
  void Dfs(int u) {
    ll l = str.size();
    for (auto v : g[u]) {
      Dfs(v);
    }
    str.push_back(S[u]);
    ll r = str.size() - 1;
    ranges[u] = {l, r};
  }

 public:
  vector<bool> findAnswer(vector<int>& parent, string s_) {
    S.swap(s_);
    ll n = parent.size();
    g.resize(n);
    for (int i = 1; i < n; i++) {
      const ll p = parent[i];
      g[p].push_back(i);
    }
    for (int i = 0; i < n; i++) {
      sort(g[i].begin(), g[i].end());
    }
    str.reserve(n);
    ans.resize(n, true);
    ranges.resize(n);
    Dfs(0);

    vector<ll> hash0(n);
    Init(str.data(), n);
    for (int i = 0; i < n; i++) {
      hash0[i] = H(ranges[i].first, ranges[i].second);
    }

    std::reverse(str.begin(), str.end());
    Init(str.data(), n);
    for (int i = 0; i < n; i++) {
      auto [l0, r0] = ranges[i];
      ll r1 = n - l0 - 1;
      ll l1 = n - r0 - 1;
      ans[i] = H(l1, r1) == hash0[i];
    }

    return ans;
  }
};