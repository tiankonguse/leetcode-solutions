// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll maximumSumOfHeights(vector<int>& maxHeights) {
    ll ans = 0;
    int n = maxHeights.size();

    for (int i = 0; i < n; i++) {  // 枚举最大高度
      ll tmp = maxHeights[i];

      int pre = maxHeights[i];
      for (int j = i - 1; j >= 0; j--) {
        pre = min(pre, maxHeights[j]);
        tmp += pre;
      }

      pre = maxHeights[i];
      for (int j = i + 1; j < n; j++) {
        pre = min(pre, maxHeights[j]);
        tmp += pre;
      }

      ans = max(ans, tmp);
    }
    return ans;
  }
};