// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minMaxGame(vector<int>& nums) {
    int n = nums.size();
    while (n > 1) {
      for (int i = 0; i < n; i += 2) {
        if (i / 2 % 2) {
          nums[i / 2] = max(nums[i], nums[i + 1]);
        } else {
          nums[i / 2] = min(nums[i], nums[i + 1]);
        }
      }
      n = n / 2;
    }
    return nums.front();
  }
};
