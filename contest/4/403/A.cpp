// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  double minimumAverage(vector<int>& nums) {
    int ans = INT_MAX;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      ans = min(ans, nums[i] + nums[n - 1 - i]);
    }
    return ans / 2.0;
  }
};