// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll minOperationsToMakeMedianK(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());

    int n = nums.size();
    int mid = n / 2;

    ll ans = 0;
    if (nums[mid] > k) {
      while (mid >= 0 && nums[mid] > k) {
        ans += nums[mid] - k;
        mid--;
      }
    } else if (nums[mid] < k) {
      while (mid < n && nums[mid] < k) {
        ans += k - nums[mid];
        mid++;
      }
    }

    return ans;
  }
};