// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
vector<int> h;
int H = 2001;

inline bool Find(int v) {
  if (v < 0 || v >= h.size()) return false;
  return h[v] > 0;
}
class Solution {
  vector<pair<int, int>> nums;
  int n;
  int ans = 0;
  int k;
  int Dfs(int p) {
    if (p == n) return 1;
    auto [val, num] = nums[p];
    // 不选择 p
    int ans = Dfs(p + 1);
    // 选择 p
    if (!Find(val + k) && !Find(val - k)) {
      h[val]++;
      ans += ((1 << num) - 1) * Dfs(p + 1);
      h[val]--;
    }
    return ans;
  }

 public:
  int beautifulSubsets(vector<int>& nums_, int k) {
    this->k = k;
    map<int, int> m;
    for (auto v : nums_) {
      m[v]++;
    }
    for (auto [k, v] : m) {
      nums.push_back({k, v});
    }
    n = nums.size();
    h.clear();
    h.resize(H, 0);
    return Dfs(0) - 1;
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
