// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int numberOfArrays(const string& s, int k) {
    int n = s.length();
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
      if (s[i - 1] == '0') {
        continue;
      }
      ll pre = 0;
      for (int j = i; j <= n; j++) {
        pre = pre * 10 + (s[j - 1] - '0');
        if (pre > k) {
          break;
        }
        dp[j] = (dp[j] + dp[i - 1]) % mod;
      }
    }
    return dp[n];
  }
};
