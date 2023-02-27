// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

  int GetMsk(int V) {
    int mask = 0;
    for (int i = 0; i < primes.size(); i++) {
      if (V % (primes[i] * primes[i]) == 0) return -1;
      if (V % primes[i] == 0) {
        mask |= 1 << i;
      }
    }
    return mask;
  }

 public:
  int squareFreeSubsets(vector<int>& nums) {
    int k = primes.size();
    vector<int> pre(1 << k, 0);
    vector<int> next(1 << k, 0);
    pre[0] = 1;
    for (int i = 0; i < nums.size(); i++) {
      int mask = GetMsk(nums[i]);
      if (mask == -1) continue;
      next = pre;
      for (int j = 0; j < (1 << k); j++) {
        if ((j & mask) == 0) {
          next[j | mask] = (next[j | mask] + pre[j]) % mod;
        }
      }
      pre.swap(next);
    }
    int ans = 0;
    for (auto v : pre) {
      ans = (ans + v) % mod;
    }
    return (ans -1 + mod) % mod;
  }
};