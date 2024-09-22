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
  long long validSubstringCount(const string& word1, const string& word2) {
    vector<ll> h2(30, 0);
    int charNum2 = 0;
    for (auto c : word2) {
      if (h2[c - 'a'] == 0) {
        charNum2++;  // 首次出现，计数一次
      }
      h2[c - 'a']++;
    }
    vector<ll> h1(30, 0);
    int charNum1 = 0;

    ll ans = 0;
    int n = word1.size();
    int r = 0;
    for (int l = 0; l < n; l++) {
      while (charNum1 < charNum2 && r < n) {  // 不满足
        int v = word1[r] - 'a';
        h1[v]++;
        if (h1[v] == h2[v]) {  // 首次匹配
          charNum1++;
        }
        r++;
      }

      if (charNum1 != charNum2) {  // 还不匹配，说明后面都没答案
        myprintf("l=%d no ans, charNum1=%d charNum2=%d \n", l, charNum1,
                 charNum2);
        break;
      }

      myprintf("l=%d ans=%lld, r=%d\n", n - r + 1, r);
      ans += (n - r + 1);  // 最后一个恰好匹配时，r == n

      if (1) {
        int v = word1[l] - 'a';
        h1[v]--;
        if (h1[v] + 1 == h2[v]) {  // 由相等转化为不等
          charNum1--;
        }
        l++;
      }
    }
    return ans;
  }
};