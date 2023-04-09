// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimizeMax(vector<int>& nums, int p) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    ll l = 0, r = nums.back() - nums.front() + 1;

    while (l < r) {  // [l, r)
      ll mid = (l + r) / 2;

      int num = 0;
      for (int i = 0; i < n && num < p; i++) {
        if (i < n && i + 1 < n && nums[i + 1] - nums[i] <= mid) {
          num++;
          i++;
        }
      }
        // printf("mid=%lld num=%d\n", mid, num);
      if (num >= p) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};