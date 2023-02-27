// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumSwap(const string& s1, const string& s2) {
    int n = s1.length();
    int xy = 0, yx = 0;
    for (int i = 0; i < n; i++) {
      if (s1[i] == s2[i]) continue;
      if (s1[i] == 'x') {
        xy++;
      } else {
        yx++;
      }
    }

    if ((xy + yx) % 2 == 1) {
      return -1;
    }

    int ans = 0;
    ans += xy / 2 + yx / 2;
    xy %= 2;
    yx %= 2;

    if (yx == 1 && yx == 1) {
      ans += 2;
    }
    return ans;
  }
};
