// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> nums;
  int Check(int V) {
    int ans = 0;
    int flag = 1;
    for (auto v : nums) {
      if (v > V) {
        flag = 1;
        continue;
      }

      if (flag == 1) {
        ans++;
        flag = 0;
      } else {
        flag = 1;
      }
    }

    return ans;
  }

 public:
  int minCapability(vector<int>& nums_, int k) {
    nums.swap(nums_);
    int l = 1, r = 0;  // [l, r)
    for (auto v : nums) {
      r = max(v + 1, r);
    }
    while (l < r) {
      int mid = (l + r) / 2;
      int K = Check(mid);
      if (K >= k) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};