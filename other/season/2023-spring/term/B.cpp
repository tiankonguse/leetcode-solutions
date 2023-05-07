// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int rampartDefensiveLine(vector<vector<int>>& rampart) {
    auto Check = [&rampart](ll mid) -> bool {  //
      if (mid == 0) return true;
      ll pre = -1 - mid;
      for (auto& v : rampart) {  // [l, r)
        ll l = v[0], r = v[1];

        if (pre > l) return false;

        if (l - pre >= mid) {
          pre = r;
          continue;
        }

        pre = pre + r - l + mid;
      }

      return true;
    };

    ll l = 0, r = INT_MAX;
    while (l < r) {  // [l, r)
      ll mid = (l + r) / 2;
      if (Check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  }
};