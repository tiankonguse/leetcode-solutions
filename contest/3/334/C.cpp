// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> nums;
  int n;
  bool Check(int mid) {
    if (mid * 2 > n) return false;
    int j = n - mid;
    for (int i = 0, j = n - mid; i < mid; i++, j++) {
      if (nums[i] * 2 > nums[j]) {
        return false;
      }
    }
    return true;
  }

 public:
  int maxNumOfMarkedIndices(vector<int>& nums_) {
    nums.swap(nums_);
    n = nums.size();
    sort(nums.begin(), nums.end());

    int l = 0, r = n;  // [l,r)
    printf("l=%d r=%d\n", l, r);
    while (l < r) {
      int mid = (l + r) / 2;
      printf("mid=%d ret=%d\n", mid, Check(mid));
      if (Check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return (r - 1) * 2;
  }
};