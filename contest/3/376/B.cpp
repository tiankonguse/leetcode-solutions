// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> divideArray(vector<int>& nums, int k) {
    int n = nums.size();
    if (n % 3 != 0) {
      return {};
    }

    sort(nums.begin(), nums.end());

    vector<vector<int>> ans;
    ans.reserve(n / 3);
    for (auto v : nums) {
      if (ans.empty() || ans.back().size() == 3) {
        ans.push_back({});
      }
      auto& list = ans.back();
      list.push_back(v);
      if (list.size() == 3 && list.back() - list.front() > k) {
        return {};
      }
    }
    return ans;
  }
};
