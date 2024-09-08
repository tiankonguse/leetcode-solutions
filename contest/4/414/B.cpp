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
  int maxPossibleScore(vector<int>& nums, ll d) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    auto Check = [&d, &nums](ll mid) -> bool {
      int n = nums.size();
      ll preVal = nums.front();
      bool useMid = false;
      for (int i = 1; i < n; i++) {
        ll val = nums[i];
        ll left = val, right = val + d;
        ll nextMinVal = preVal + mid;

        if (nextMinVal > right) {
          return false;
        }

        if (nextMinVal < left) {
          preVal = left;
        } else if (left <= nextMinVal && nextMinVal <= right) {
          useMid = true;
          preVal = nextMinVal;
        }
      }
      return true;
    };

    ll left = 0, right = nums.back() + d + 1;
    // myprintf("left=%lld right=%lld\n", left, right);
    while (left < right) {
      ll mid = (left + right) / 2;
      if (Check(mid)) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left - 1;
  }
};