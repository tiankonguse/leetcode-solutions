// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findTheLongestBalancedSubstring(string s) {
    int ans = 0;
    int preZero = 0;
    int preOne = 0;
    int state = 0;
    for (auto c : s) {
      if (c == '0') {
        if (state == 1) {
          preZero = 0;
          preOne = 0;
          state = 0;
        }
        preZero++;
      } else {
        if (state == 0) {
          state = 1;
        }
        preOne++;
        ans = max(ans, min(preZero, preOne) * 2);
      }
    }

    return ans;
  }
};