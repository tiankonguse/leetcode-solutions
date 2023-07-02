// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll minCost(vector<int>& nums, int x) {
    vector<int> ansVal = nums;
    ll sum = accumulate(nums.begin(), nums.end(), 0ll);
    ll ans = sum;

    int n = nums.size();
    for (int k = 1; k < n; k++) {
      sum = sum + x;
      for (int i = 0; i < n; i++) {
        int p = (i + k) % n;
        if (ansVal[i] > nums[p]) {
          sum = sum - ansVal[i] + nums[p];
          ansVal[i] = nums[p];
        }
      }
      ans = min(ans, sum);
    }

    return ans;
  }
};