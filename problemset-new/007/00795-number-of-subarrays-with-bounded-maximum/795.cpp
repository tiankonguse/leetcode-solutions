#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
    int n = nums.size();

    ll ans = 0;
    vector<pair<ll, ll>> dp(n + 1, {n + 1, n + 1});

    ll firstMidPos = n;
    ll firstMaxPos = n;
    for (int i = n - 1; i >= 0; i--) {
      ll v = nums[i];
      if (v > right) {
        firstMaxPos = i;
      }
      if (v >= left && v <= right) {
        firstMidPos = i;
      }

      if (firstMidPos < firstMaxPos) {
        ans += firstMaxPos - firstMidPos;
      }
    }

    return ans;
  }
};