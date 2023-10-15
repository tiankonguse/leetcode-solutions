// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string shortestBeautifulSubstring(string s, const int k) {
    int ansL = 0, ansR = 0;
    int n = s.length();
    int len = n + 1;
    const char* p = s.data();
    // printf("in s=%s k=%d\n", p, k);

    int l = 0, r = 0, K = 0;
    while (l < n) {
      while (l < n && s[l] == '0') {
        l++;
      }
      r = max(l, r);

      while (r < n && K < k) {
        if (s[r] == '1') {
          K++;
        }
        r++;
      }

      if (K < k) break;

      // printf("l=%d r=%d s=%s\n", l, r, s.substr(l, r - l).c_str());

      if (r - l < len) {
        len = r - l;
        ansL = l;
        ansR = r;
      } else if (r - l == len) {
        if (strncmp(p + l, p + ansL, len) < 0) {
          ansL = l;
          ansR = r;
        }
      }

      l++;
      K--;
      // printf("l=%d, K=%d \n", l, K);
    }
    len = ansR - ansL;
    return s.substr(ansL, len);
  }
};