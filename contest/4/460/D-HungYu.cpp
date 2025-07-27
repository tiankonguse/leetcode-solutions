
#include <bits/stdc++.h>
class Solution {
 public:
  long long maximizeXorAndXor(vector<int>& nums) {
    int n = nums.size();
    int fullXor = 0;
    for (int x : nums) fullXor ^= x;
    long long ans = 0;
    int N = 1 << n;
    for (int mask = 0; mask < N; mask++) {
      long long andB = 0;
      bool emptyB = true;
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
          if (emptyB) {
            andB = nums[i];
            emptyB = false;
          } else {
            andB &= nums[i];
          }
        }
      }
      if (emptyB) andB = 0;
      int xorB = 0;
      for (int i = 0; i < n; i++)
        if (mask & (1 << i)) xorB ^= nums[i];
      long long Txor = fullXor ^ xorB;
      long long maskKeep = ~Txor;
      long long basis[31] = {};
      for (int i = 0; i < n; i++)
        if (!(mask & (1 << i))) {
          long long v = nums[i] & maskKeep;
          for (int b = 30; b >= 0 && v; b--) {
            if (v & (1LL << b)) {
              if (!basis[b]) {
                basis[b] = v;
                break;
              }
              v ^= basis[b];
            }
          }
        }
      long long maxM = 0;
      for (int b = 30; b >= 0; b--) {
        if ((maxM ^ basis[b]) > maxM) {
          maxM ^= basis[b];
        }
      }
      long long bestAC = Txor + 2LL * maxM;
      ans = max(ans, andB + bestAC);
    }
    return ans;
  }
};