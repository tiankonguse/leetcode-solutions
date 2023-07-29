// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  long long maxArrayValue(vector<int>& nums) {
    ll ans = 0;

    int n = nums.size();
    ll sum = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (nums[i] <= sum) {
        sum += nums[i];
      } else {
        sum = nums[i];
      }
      ans = max(ans, sum);
    }

    return ans;
  }
};