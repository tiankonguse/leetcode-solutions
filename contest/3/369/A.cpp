// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findKOr(vector<int>& nums, int k) {
    vector<int> bits(32, 0);
    for (ll v : nums) {
      for (int i = 0; v; i++) {
        if (v & 1) {
          bits[i]++;
        }
        v = v / 2;
      }
    }

    ll ans = 0;
    for (int i = 0; i < 32; i++) {
      if (bits[i] >= k) {
        ans |= 1 << i;
      }
    }
    return ans;
  }
};