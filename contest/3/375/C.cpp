// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  ll countSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> stat;

    int maxVal = nums.front();
    for (auto v : nums) {
      maxVal = max(maxVal, v);
    }

    for (int i = 0; i < n; i++) {
      int v = nums[i];
      if (v == maxVal) {
        stat.push_back(i);
      }
    }

    ll ans = 0;
    int prePos = -1;
    for (int offset = 0; offset + k <= stat.size(); offset++) {
      int l = stat[offset];
      int r = stat[offset + k - 1];
      // 至少有一个答案
      ll leftNum = stat[offset] - prePos;
      ll rightNum = n - r;
      printf("i=%d leftNum=%lld, rightNum=%lld\n", l, leftNum, rightNum);
      ans += leftNum * rightNum;
      prePos = stat[offset];
    }
    return ans;
  }
};