// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
vector<int> h;
int H = 2001;
stack<int> sta;

inline bool Find(int v) {
  if (v < 0 || v >= H) return false;
  return h[v] > 0;
}
inline void Clear() {
  while (!sta.empty()) {
    h[sta.top()] = 0;
    sta.pop();
  }
}

class Solution {
  vector<int> nums;
  int n;
  int ans = 0;
  bool Check(int mask, int k) {
    Clear();
    for (int i = 0; i < n; i++) {
      if (mask & (1 << i)) {
        if (Find(nums[i] + k) || Find(nums[i] - k)) {
          return false;
        }
        h[nums[i]] = 1;
        sta.push(nums[i]);
      }
    }
    return true;
  };

 public:
  int beautifulSubsets(vector<int>& nums_, int k) {
    nums.swap(nums_);
    int ans = 0;
    n = nums.size();
    h.resize(H, 0);
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
