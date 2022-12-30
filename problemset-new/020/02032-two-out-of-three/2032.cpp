// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2,
                            vector<int>& nums3) {
    vector<int> nums(111, 0);

    for (auto v : nums1) {
      nums[v] |= 1 << 0;
    }
    for (auto v : nums2) {
      nums[v] |= 1 << 1;
    }
    for (auto v : nums3) {
      nums[v] |= 1 << 2;
    }

    vector<int> ans;

    for (int i = 0; i < nums.size(); i++) {
      if (__builtin_popcount(nums[i]) > 1) {
        ans.push_back(i);
      }
    }

    return ans;
  }
};