// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> nums;
  int n;
  unordered_set<int> h;
  bool Check(int mask, int k) {
    h.clear();
    for (int i = 0; i < n; i++) {
      if (mask & (1 << i)) {
        if (h.count(nums[i] + k) || h.count(nums[i] - k)) {
          return false;
        }
        h.insert(nums[i]);
      }
    }
    return true;
  };

 public:
  int beautifulSubsets(vector<int>& nums_, int k) {
    nums.swap(nums_);
    int ans = 0;
    n = nums.size();
    h.reserve(2000);
    int N = 1 << n;

    for (int i = 1; i < N; i++) {
      if (Check(i, k)) {
        ans++;
      }
    }
    return ans;
  }
};

int main() {
  int ans;
  vector<int> nums;
  int k;

  ans = 4;
  nums = {2, 4, 6};
  k = 2;
  TEST_SMP2(Solution, beautifulSubsets, ans, nums, k);

  ans = 1;
  nums = {1};
  k = 1;
  TEST_SMP2(Solution, beautifulSubsets, ans, nums, k);

  ans = 155519;
  nums = {20, 14, 22, 1,  4,  11, 21, 19, 29, 25,
          12, 18, 9,  15, 23, 6,  27, 16, 26, 5};
  k = 13;
  TEST_SMP2(Solution, beautifulSubsets, ans, nums, k);
  return 0;
}
