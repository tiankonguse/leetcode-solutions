// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countWays(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int ans = 0;
    int l = 0;
    // 不选择
    if (nums[0] > 0) {
      ans++;
    }

    for (int i = 0; i + 1 < n; i++) {  // 选择 i
      l++;
      if (l > nums[i] && l < nums[i + 1]) {
        ans++;
      }
    }

    // 都选择
    l = n;
    if (l > nums.back()) {
      ans++;
    }
    return ans;
  }
};