// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumSum(vector<int>& nums) {
    int n = nums.size();
    vector<ll> left(n + 2, INT_MAX);
    vector<ll> right(n + 2, INT_MAX);

    for (int i = 1; i <= n; i++) {
      ll v = nums[i - 1];
      left[i] = min(left[i - 1], v);
    }
    for (int i = n; i >= 1; i--) {
      ll v = nums[i - 1];
      right[i] = min(right[i + 1], v);
    }

    ll ans = INT_MAX;
    for (int i = 2; i < n; i++) {
      ll v = nums[i - 1];
      if (left[i - 1] < v && v > right[i + 1]) {
        ans = min(ans, left[i - 1] + v + right[i + 1]);
      }
    }
    if (ans == INT_MAX) {
      ans = -1;
    }
    return ans;
  }
};