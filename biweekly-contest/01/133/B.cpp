// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  // 连续
  int minOperations(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i + 2 < n; i++) {
      if (nums[i] == 1) continue;
      ans++;
      for (int j = 0; j < 3; j++) {
        nums[i + j] = 1 - nums[i + j];
      }
    }

    if (nums[n - 2] + nums[n - 1] < 2) return -1;

    return ans;
  }
};