// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int mod = 1000000007;
class Solution {
 public:
  int maxSum(vector<int>& nums, int k) {
    const int BIT = 31;
    vector<int> bits(BIT, 0);
    for (auto v : nums) {
      int bit = 0;
      while (v) {
        if (v % 2 == 1) {
          bits[bit]++;
        }
        v = v / 2;
        bit++;
      }
    }

    ll ans = 0;
    for (int i = 0; i < k; i++) {
      ll v = 0;
      for (int j = 0; j < BIT; j++) {
        if (bits[j] > 0) {
          v |= 1 << j;
          bits[j]--;
        }
      }
      if(v == 0) break;
      ans = (ans + v * v) % mod;
    }

    return ans;
  }
};