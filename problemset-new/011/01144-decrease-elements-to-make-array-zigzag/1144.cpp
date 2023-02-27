// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> nums;
  int n;
  int Get(int i) {
    if (i < 0 || i >= n) return INT_MAX;
    return nums[i];
  }
  int Solver(int index) {  //
    int ans = 0;
    for (int i = index; i < n; i += 2) {
      int minVal = min(Get(i - 1), Get(i + 1));
      if (nums[i] >= minVal) {
        ans += nums[i] - minVal + 1;
      }
    }
    return ans;
  }

 public:
  int movesToMakeZigzag(vector<int>& nums_) {
    nums.swap(nums_);
    n = nums.size();
    return min(Solver(0), Solver(1));
  }
};