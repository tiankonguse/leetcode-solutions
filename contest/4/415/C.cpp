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

const ll BASE7 = 29;
const ll BASE9 = 29;

class Solution {
  vector<ll> dp;
  vector<unordered_set<ll>> h;
  int n;
  int MAXANS;

 public:
  int minValidStrings(vector<string>& words, const string& target) {
    n = target.size();
    MAXANS = n + 1;
    h.resize(n + 1);

    for (auto& word : words) {
      ll pre7 = 0;
      ll pre9 = 0;
      for (int i = 0; i < word.size() && i < n; i++) {
        const char v = word[i];
        pre7 = (pre7 * BASE7 + (v - 'a' + 1)) % mod1e7;
        pre9 = (pre9 * BASE9 + (v - 'a' + 1)) % mod1e9;
        const ll pre = (pre7 << 32) | pre9;
        h[i + 1].insert(pre);
      }
    }

    dp.resize(n + 1, MAXANS);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
      if (dp[i - 1] >= MAXANS) continue;
      ll pre7 = 0;
      ll pre9 = 0;
      for (int j = i; j <= n; j++) {
        const char v = target[j - 1];
        pre7 = (pre7 * BASE7 + (v - 'a' + 1)) % mod1e7;
        pre9 = (pre9 * BASE9 + (v - 'a' + 1)) % mod1e9;
        const ll pre = (pre7 << 32) | pre9;
        if (h[j - i + 1].count(pre)) {
          dp[j] = min(dp[j], 1 + dp[i - 1]);
        } else {
          break;
        }
      }
    }
    if (dp[n] >= MAXANS) return -1;
    return dp[n];
  }
};