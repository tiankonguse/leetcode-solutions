// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int maximumTastiness(vector<int>& price, int k) {
    sort(price.begin(), price.end());

    ll l = 0, r = price.back() - price.front() + 1;
    while (l < r) {
      ll mid = (l + r) / 2;

      int num = 0;
      auto it = price.begin();
      while (it != price.end() && num < k) {
        num++;
        it = lower_bound(it, price.end(), *it + mid);
      }

      if (num >= k) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l-1;
  }
};
