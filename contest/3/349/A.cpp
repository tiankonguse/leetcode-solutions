// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findNonMinOrMax(vector<int>& nums) {
    if (nums.size() <= 2) {
      return -1;
    }
    sort(nums.begin(), nums.end());
    return nums[1];
  }
};