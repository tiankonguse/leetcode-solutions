// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minOrAfterOperations(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;
    for (int i = 29; i >= 0; i--) {
      int tmpAns = 0;
      ll pre = 0;
      for (auto v : nums) {
        ll vv = (v & ~ans) >> i;

        if (pre == 0) {
          pre = vv;
          continue;
        }

        pre = pre & vv;
        tmpAns++;
      }
      if (pre) {
        tmpAns++;
      }

      if (tmpAns > k) {
        ans |= 1 << i;
      }
    }
    return ans;
  }
};