// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  long long findMaximumScore(vector<int>& nums) {
    ll n = nums.size();
    ll ans = 0;
    ll preVal = nums.front();
    ll prePos = 0;
    for (int i = 1; i < n; i++) {
      ll v = nums[i];
      if (v > preVal) {
        ans += (i - prePos) * preVal;
        preVal = v;
        prePos = i;
      }
    }
    ans += (n - 1 - prePos) * preVal;
    return ans;
  }
};