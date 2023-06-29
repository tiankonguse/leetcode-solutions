// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findValueOfPartition(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int ans = nums.back() - nums.front();
    for (int i = 1; i < nums.size(); i++) {
      ans = min(ans, nums[i] - nums[i - 1]);
    }
    return ans;
  }
};