// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int addMinimum(string word) {
    int ans = 0;
    char pre = 'c';
    for (auto v : word) {
      if (pre + 1 == v || (pre == 'c' && v == 'a')) {
      } else if (pre == v) {
        ans += 2;
      } else {
        ans += 1;
      }
      pre = v;
    }
    ans += 'c' - pre;
    return ans;
  }
};