// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll NextHash(ll pre, char v) {
  ll pre7 = pre >> 32;
  ll pre9 = pre << 32 >> 32;
  pre7 = (pre7 * BASE + (v - 'a' + 1)) % mod1e7;
  pre9 = (pre9 * BASE + (v - 'a' + 1)) % mod1e9;
  return (pre7 << 32) | pre9;
}

class Solution {
  vector<ll> dp;
  unordered_set<ll> h;
  string target;
  int n;
  int MAXANS;

  ll Dfs(const int p) {
    ll& ret = dp[p];
    if (ret != -1) return ret;
    ret = MAXANS;

    ll pre = 0;
    for (int i = p; i < n; i++) {
      pre = NextHash(pre, target[i]);
      if (h.count(pre)) {
        ret = min(ret, 1 + Dfs(i + 1));
      } else {
        break;
      }
    }

    return ret;
  }

 public:
  int minValidStrings(vector<string>& words, string target_) {
    target.swap(target_);
    n = target.size();
    ll sum = 0;
    for (auto& word : words) {
      sum += word.size();
    }
    h.rehash(sum);

    for (auto& word : words) {
      ll pre = 0;
      for (int i = 0; i < word.size() && i < n; i++) {
        pre = NextHash(pre, word[i]);
        h.insert(pre);
      }
    }

    MAXANS = n + 1;
    dp.resize(n + 1, -1);
    dp[n] = 0;
    ll ans = Dfs(0);
    if (ans >= MAXANS) ans = -1;
    return ans;
  }
};