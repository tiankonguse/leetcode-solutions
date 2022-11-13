#include <bits/stdc++.h>

#include "base.h"
using namespace std;


class Solution {
 public:
  int subarrayLCM(vector<int>& nums, int k) {
    int ans = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
      int val = 1;
      for (int j = i; j < n; j++) {
        val = val * nums[j] / gcd(val, nums[j]);
        if (val == k) ans++;
        if (val > k) break;
      }
    }
    return ans;
  }
};