// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int longestAlternatingSubarray(vector<int>& nums, int threshold) {
    int n = nums.size();

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (nums[i] % 2 != 0) continue;
      if (nums[i] > threshold) continue;
      int tmpAns = 1;
      for (int j = i + 1; j < n; j++) {
        if (nums[j] > threshold) break;
        if (nums[j] % 2 == nums[j - 1] % 2) break;
        tmpAns++;
      }
      ans = max(ans, tmpAns);
    }
    return ans;
  }
};