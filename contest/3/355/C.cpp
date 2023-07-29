// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;

 public:
  int maxIncreasingGroups(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end(), [](auto& a, auto& b) { return a > b; });

    auto Check = [&nums](int ans) {
      int lev = ans;
      int leftNum = lev;

      for (auto v : nums) {
        if (v < leftNum) {
          leftNum -= v;
        } else if (v == leftNum) {
          lev--;
          if (lev == 0) return true;
          leftNum = lev;
        } else {
          lev--;
          if (lev == 0) return true;

          v -= leftNum;
          int nextMaxUseNum = lev - (leftNum - 1);
          leftNum = lev;

          if (v >= nextMaxUseNum) {
            leftNum -= nextMaxUseNum;
          } else {
            leftNum -= v;
          }
          if (leftNum == 0) {
            lev--;
            if (lev == 0) return true;
            leftNum = lev;
          }
        }
      }
      return false;
    };

    int l = 1, r = n + 1;
    while (l < r) {
      int mid = (l + r) / 2;
      if (Check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }

    return r - 1;
  }
};