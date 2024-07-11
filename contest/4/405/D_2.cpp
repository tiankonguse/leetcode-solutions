// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

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

ll Hash(const char* str, int l, int r) {
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

void update(int& ans, int v) {
  if (ans == -1) {
    ans = v;
  } else {
    ans = min(ans, v);
  }
}

class Solution {
 public:
  int minimumCost(const string& target, vector<string>& words,
                  vector<int>& costs) {
    int n = target.size();
    Init(target.data(), n);

    unordered_map<ll, int> h;
    set<int> HS;
    for (int i = 0; i < words.size(); i++) {
      string& W = words[i];
      ll w = Hash(W.data(), 0, W.size());
      int c = costs[i];
      HS.insert(W.size());
      if (h.count(w)) {
        h[w] = min(h[w], c);
      } else {
        h[w] = c;
      }
    }

    vector<int> dp;
    dp.resize(n + 1, -1);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
      if (dp[i] == -1) continue;
      for (auto hs : HS) {
        if (i + hs > n) break;
        ll w = H(i, i + hs - 1);
        if (h.count(w)) {
          update(dp[i + hs], dp[i] + h[w]);
        }
      }
    }
    return dp[n];
  }
};