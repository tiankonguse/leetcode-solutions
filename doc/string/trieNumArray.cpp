#include "base.h"

typedef long long ll;
const int maxBit = 23;

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