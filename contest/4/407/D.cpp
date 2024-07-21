// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long minimumOperations(const vector<int>& nums,
                              const vector<int>& target) {
    int n = nums.size();
    ll preVal = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ll nowVal = target[i] - nums[i];

      // 符号变化，计算答案
      if (preVal * nowVal <= 0) {
        ans += abs(preVal);
        preVal = nowVal;
        continue;
      }

      // 符号相同
      ll tmpPreVal = abs(preVal);
      ll tmpNowVal = abs(nowVal);
      if (tmpPreVal > tmpNowVal) {
        ans += tmpPreVal - tmpNowVal;
      }
      preVal = nowVal;
    }
    ans += abs(preVal);
    return ans;
  }
};
