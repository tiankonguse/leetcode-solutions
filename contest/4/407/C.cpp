// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxOperations(const string& s) {
    int one = 0;
    int pre = 1;
    int ans = 0;
    for (auto c : s) {
      int now = c - '0';
      if (now == 1) {
        one++;
      }

      if (pre == 1 && now == 0) {
        ans += one;
      }
      pre = now;
    }
    return ans;
  }
};