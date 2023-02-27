// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long countFairPairs(vector<int>& nums, int lower, int upper) {
    sort(nums.begin(), nums.end());
    long long ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {  // [l, r)
      ll v = nums[i];
      ll minVal = lower - v;
      int maxVal = upper - v;
      int l = lower_bound(nums.begin(), nums.end(), minVal) - nums.begin();
      int r = upper_bound(nums.begin(), nums.end(), maxVal) - nums.begin();

      int d = r - l;  //[l, r)
      if (l <= i && i < r) {
        d--;
      }
      ans += d;
    }

    return ans / 2;
  }
};