// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool canSplitArray(vector<int>& nums, int m) {
    int n = nums.size();
    if (n == 1 || n == 2) return true;
    for (int i = 1; i < n; i++) {
      if (nums[i] + nums[i - 1] >= m) return true;
    }
    return false;
  }
};
