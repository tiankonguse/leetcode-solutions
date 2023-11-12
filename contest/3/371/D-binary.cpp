// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int maxBit = 23;
class Solution {
  int BinarySearch(const vector<int>& nums, int l, int r, int i) {
    // [l, r)
    while (l < r) {
      const int mid = (l + r) / 2;
      const int bit = (nums[mid] >> i) & 1;
      if (bit) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }
int Solver(const vector<int>& nums, int l, int r, int y) {
  // [l, r)
  for (int i = maxBit; i >= 0; i--) {
    // 区间内，查找第 i 位首次出现 1 的位置
    const int mid = BinarySearch(nums, l, r, i);
    const int bit = (y >> i) & 1;

    if (bit == 0) {
      if (mid < r) {  // 存在位1区间
        l = mid;
      } else {  // 不存在位1区间
        continue;
      }
    } else {
      if (l < mid) {  //存在位0区间
        r = mid;
      } else {  //存在位0区间
        continue;
      }
    }
  }
  return nums[l] ^ y;
}

 public:
  int maximumStrongPairXor(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    int ans = 0;
    for (int i = 0, r = 0; i < n; i++) {  //[i, r)
      const int y = nums[i];
      const int y2 = y * 2;

      while (r < n && nums[r] <= y2) {
        r++;
      }

      const int tmp = Solver(nums, i, r, y);
      // printf("[y=%d y2=%d], ans=%d\n", y, y2, tmp);
      ans = max(ans, tmp);
    }
    return ans;
  }
};