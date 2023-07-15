// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  // 0 <= i < j < n
  // -target <= nums[j] - nums[i] <= target
  // nums[i] - target <= nums[j] <=  nums[i] + target
  // nums[i] <= nums[j] + target
  // nums[i] >= nums[j] - target
  int maximumJumps(vector<int>& nums, ll target) {
    int n = nums.size();
    vector<int> maxStep(n, -1);
    maxStep[0] = 0;

    for (int i = 0; i < n; i++) {
      // printf("i=%d val=%d\n", i, maxStep[i]);
      if (maxStep[i] == -1) continue;
      for (int j = i + 1; j < n; j++) {
        if (nums[i] - target <= nums[j] && nums[j] <= nums[i] + target) {
          maxStep[j] = max(maxStep[j], maxStep[i] + 1);
        }
      }
    }
    return maxStep.back();
  }
};