// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int countKConstraintSubstrings(const string& s, int k) {
    int ans = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
      int dp[2] = {0, 0};
      for (int j = i; j < n; j++) {
        dp[s[j] - '0']++;
        if (dp[0] <= k || dp[1] <= k) {
          ans++;
        }else{
            break;
        }
      }
    }
    return ans;
  }
};
