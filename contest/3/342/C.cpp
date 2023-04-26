// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
    int n = nums.size();
    vector<int> ans;
    ans.reserve(n - k + 1);

    for (auto& v : nums) {
      v += 50;
    }

    vector<int> flags(110);

    const auto& Check = [&flags, &x]() -> int {
      int sum = 0;
      for (int i = 0; i <= 100; i++) {
        sum += flags[i];
        if (sum >= x) {
          return i >= 50 ? 0 : i - 50;
        }
      }
      return 0;
    };

    for (int i = 0; i < n; i++) {
      flags[nums[i]]++;
      if (i < k - 1) {
        continue;
      }
      ans.push_back(Check());
      flags[nums[i - k + 1]]--;
    }
    return ans;
  }
};