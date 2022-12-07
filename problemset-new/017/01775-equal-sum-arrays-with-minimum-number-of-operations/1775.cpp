// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> dp1;
  vector<int> dp2;
  vector<int> nums1;
  vector<int> nums2;

  void init() {
    dp1.resize(7, 0);
    for (auto v : nums1) {
      dp1[v]++;
    }
    dp2.resize(7, 0);
    for (auto v : nums2) {
      dp2[v]++;
    }
  }

  int GetMin(int t, vector<int>& nums, vector<int>& dp) {
    int sum = dp[1];
    for (int i = 6; i > 1; i--) {
      if (t >= dp[i]) {
        sum += dp[i];
        t -= dp[i];
      } else {
        sum += t;
        sum += (dp[i] - t) * i;
        t = 0;
      }
    }
    return sum;
  }
  int GetMax(int t, vector<int>& nums, vector<int>& dp) {
    int sum = dp[6] * 6;
    for (int i = 1; i < 6; i++) {
      if (t >= dp[i]) {
        sum += dp[i] * 6;
        t -= dp[i];
      } else {
        sum += t * 6;
        sum += (dp[i] - t) * i;
        t = 0;
      }
    }
    return sum;
  }

  pair<int, int> GetRange(int t, vector<int>& nums, vector<int>& dp) {
    return {GetMin(t, nums, dp), GetMax(t, nums, dp)};
  }

  bool check(int mid) {
    for (int i = 0; i <= mid; i++) {
      int j = mid - i;
      // 尝试修改 nums1 i 次，判断两个最大值与最小值是否有重叠
      auto p1 = GetRange(i, nums1, dp1);
      auto p2 = GetRange(j, nums2, dp2);
      // printf("left=%d [%d,%d]\n", i, p1.first, p1.second);
      // printf("right=%d [%d,%d]\n", j, p2.first, p2.second);
      if (p1.first > p2.first) {
        swap(p1, p2);
      }
      if (p1.second >= p2.first) {
        return true;
      }
    }
    return false;
  }

 public:
  int minOperations(vector<int>& nums1_, vector<int>& nums2_) {
    nums1.swap(nums1_);
    nums2.swap(nums2_);

    if (nums1.size() > nums2.size()) {
      swap(nums1, nums2);
    }

    if (nums1.size() * 6 < nums2.size()) {
      return -1;
    }

    // 此时肯定有答案

    init();

    int left = 0, right = nums1.size() + nums2.size();

    while (left < right) {
      int mid = (left + right) / 2;
      if (check(mid)) {
        // printf("left=%d right=%d mid=%d ", left, right, mid);
        //    printf("ok \n");
        right = mid;
      } else {
        //    printf("left=%d right=%d mid=%d ", left, right, mid);
        //    printf("not ok \n");
        left = mid + 1;
      }
    }
    return left;
  }
};