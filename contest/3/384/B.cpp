// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
    int ans = 0;
    int n = nums.size();
    int m = pattern.size();
    auto Check = [&](int i) -> bool {
      for (int j = 0; j < m; j++) {
        if (i + j + 1 >= n) return false;
        if (pattern[j] == 0) {
          if (nums[i + j] == nums[i + j + 1]) {
            continue;
          } else {
            return false;
          }
        } else if (pattern[j] == -1) {
          if (nums[i + j] > nums[i + j + 1]) {
            continue;
          } else {
            return false;
          }
        } else if (pattern[j] == 1) {
          if (nums[i + j] < nums[i + j + 1]) {
            continue;
          } else {
            return false;
          }
        }
      }
      return true;
    };
    for (int i = 0; i + m < n; i++) {
      if (Check(i)) {
        ans++;
      }
    }
    return ans;
  }
};