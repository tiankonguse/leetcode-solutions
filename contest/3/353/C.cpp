// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    vector<int> dp;
    dp.reserve(n);
    dp.push_back(min(nums1[0], nums2[0]));
    for (int i = 1; i < n; i++) {
      int v1 = nums1[i];
      int v2 = nums2[i];
      if (v1 > v2) {
        swap(v1, v2);
      }
      auto p1 = upper_bound(dp.begin(), dp.end(), v1) - dp.begin();
      auto p2 = upper_bound(dp.begin(), dp.end(), v2) - dp.begin();

      if (p1 == p2) {
        if (p1 == dp.size()) {
          dp.push_back(v1);
        } else {
          dp[p1] = v1;
        }
      } else {  // p1 < p2
        dp[p1] = v1;
        if (p2 == dp.size()) {
          dp.push_back(v2);
        } else {
          dp[p2] = v2;
        }
      }
    }
    return dp.size();
  }
};