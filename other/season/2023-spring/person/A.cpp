// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> supplyWagon(vector<int>& nums) {
    int target = nums.size() / 2;

    while (nums.size() > target) {
      int index = 0;
      int sum = nums[0] + nums[1];

      int n = nums.size();
      for (int i = 1; i + 1 < n; i++) {
        int tmp = nums[i] + nums[i + 1];
        if (tmp < sum) {
          index = i;
          sum = tmp;
        }
      }

      nums[index] += nums[index + 1];
      index++;
      while (index + 1 < n) {
        nums[index] = nums[index + 1];
        index++;
      }
      nums.pop_back();
    }
    return nums;
  }
};
