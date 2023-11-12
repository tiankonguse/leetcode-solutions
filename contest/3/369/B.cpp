// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long minSum(vector<int>& nums1, vector<int>& nums2) {
    ll zero1 = 0, zero2 = 0;
    ll sum1 = 0, sum2 = 0;
    for (ll v : nums1) {
      if (v == 0) {
        zero1++;
        sum1 += 1;
      } else {
        sum1 += v;
      }
    }
    for (ll v : nums2) {
      if (v == 0) {
        zero2++;
        sum2 += 1;
      } else {
        sum2 += v;
      }
    }

    if (zero1 == 0 && zero2 == 0) {
      if (sum1 != sum2) {
        return -1;
      }
      return sum1;
    } else if (zero2 == 0) {
      if (sum1 > sum2) {
        return -1;
      }
      return sum2;
    } else if (zero1 == 0) {
      if (sum1 < sum2) {
        return -1;
      }
      return sum1;
    } else {
      return max(sum1, sum2);
    }
  }
};