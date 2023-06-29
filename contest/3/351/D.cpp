// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> survivedRobotsHealths(vector<int>& positions,
                                    vector<int>& healths, string directions) {
    int n = positions.size();
    vector<tuple<int, int, char, int>> nums;
    nums.reserve(n);
    for (int i = 0; i < n; i++) {
      __builtin_popcount(3);
      nums.push_back({positions[i], healths[i], directions[i], i});
    }
    sort(nums.begin(), nums.end());

    vector<int> sta;
    sta.reserve(n);
    for (int i = 0; i < n; i++) {
      if (sta.empty()) {
        sta.push_back(i);
        continue;
      }
      while (!sta.empty()) {
        auto [p1, h1, d1, i1] = nums[i];
        auto [p0, h0, d0, i0] = nums[sta.back()];
        if (d0 == d1) {
          sta.push_back(i);
          break;
        }
        if (d0 == 'L' && d1 == 'R') {  // 相反方向出发
          sta.push_back(i);
          break;
        }

        // 相撞
        if (h0 < h1) {
          nums[sta.back()] = {p0, 0, d0, i0};
          sta.pop_back();
          nums[i] = {p1, h1 - 1, d1, i1};
        } else if (h0 > h1) {
          nums[i] = {p1, 0, d1, i1};
          nums[sta.back()] = {p0, h0 - 1, d0, i0};
          break;
        } else {
          nums[sta.back()] = {p0, 0, d0, i0};
          nums[i] = {p1, 0, d1, i1};
          sta.pop_back();
          break;
        }
      }
    }

    vector<int> ans;
    ans.reserve(n);
    sort(nums.begin(), nums.end(), [](auto& a0, auto& a1) {
      auto [p0, h0, d0, i0] = a0;
      auto [p1, h1, d1, i1] = a1;
      return i0 < i1;
    });
    for (auto [p, h, d, i] : nums) {
      if (h > 0) {
        ans.push_back(h);
      }
    }
    return ans;
  }
};