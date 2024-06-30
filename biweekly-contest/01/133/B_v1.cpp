// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  // 任意选择，可以不连续
  int minOperations1(vector<int>& nums) {
    int zero = 0;
    for (auto v : nums) {
      if (v == 0) {
        zero++;
      }
    }

    int ans = 0;
    if (zero) {
      ans += zero / 2;
      zero = zero % 3;
    }

    if (zero) {
      if (nums.size() == 3) return -1;  // 无解；
      ans += 3 - zero;
    }
    return ans;
  }

};