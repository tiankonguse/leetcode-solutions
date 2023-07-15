// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int ans = 1;
    int ans1 = 1, ans2 = 1;
    for (int i = 1; i < n; i++) {
      int tmp1 = 1;
      if (nums1[i] >= nums1[i - 1]) tmp1 = max(tmp1, ans1 + 1);
      if (nums1[i] >= nums2[i - 1]) tmp1 = max(tmp1, ans2 + 1);

      int tmp2 = 1;
      if (nums2[i] >= nums1[i - 1]) tmp2 = max(tmp2, ans1 + 1);
      if (nums2[i] >= nums2[i - 1]) tmp2 = max(tmp2, ans2 + 1);

      ans1 = tmp1;
      ans2 = tmp2;
      ans = max(ans, ans1);
      ans = max(ans, ans2);
    }
    return ans;
  }
};