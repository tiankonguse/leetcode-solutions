// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int longestEqualSubarray(vector<int>& nums, int k) {
    unordered_map<int, vector<int>> h;
    for (int i = 0; i < nums.size(); i++) {
      h[nums[i]].push_back(i);
    }

    auto Solver = [](vector<int>& nums, int k) -> int {
      int ans = 1;
      int l = 0, r = 0;  // [l, r]
      int n = nums.size();
      while (r < n) {
        if (r < l) {
          r = l;
        }
        int allNum = nums[r] - nums[l] + 1;
        int valNum = r - l + 1;
        if (valNum + k < allNum) {
          l++;
          continue;
        }
        ans = max(ans, valNum);
        r++;
      }

      return ans;
    };

    int ans = 0;
    for (auto& [_, v] : h) {
      ans = max(ans, Solver(v, k));
    }
    return ans;
  }
};