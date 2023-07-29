// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumBeauty(vector<int>& nums, int k) {
    int n = nums.size();
    vector<pair<int, int>> dp;
    dp.reserve(n * 2);

    for (auto v : nums) {
      dp.push_back({v - k, 1});
      dp.push_back({v + k, -1});
    }
    sort(dp.begin(), dp.end(), [](const auto& a, const auto& b) {
      if (a.first == b.first) {
        return a.second > b.second;
      }
      return a.first < b.first;
    });

    int pre = 0;
    int ans = 0;

    for (auto [v, op] : dp) {
      if (op == 1) {
        pre++;
        ans = max(ans, pre);
      } else {
        pre--;
      }
    }

    return ans;
  }
};
