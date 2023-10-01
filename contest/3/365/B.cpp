// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long maximumTripletValue(vector<int>& nums) {
    int n = nums.size();
    vector<ll> left(n), right(n);
    for (int i = 1; i < n; i++) {
      left[i] = max(left[i - 1], ll(nums[i - 1]));
    }
    for (int i = n - 2; i >= 0; i--) {
      right[i] = max(right[i + 1], ll(nums[i + 1]));
    }
    ll ans = 0;
    for (int i = 1; i + 1 < n; i++) {
      ans = max(ans, (left[i] - nums[i]) * right[i]);
    }
    return ans;
  }
};
