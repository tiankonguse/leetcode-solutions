// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumChairs(string s) {
    int ans = 0;
    int now = 0;
    for (auto c : s) {
      if (c == 'E') {
        now++;
      } else {
        now--;
      }
      ans = max(ans, now);
    }
    return ans;
  }
};