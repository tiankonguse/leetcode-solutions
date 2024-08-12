// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
int maxVal = 1001;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int countOfPairs(vector<int>& nums) {
    vector<ll> preSum(maxVal, 0);
    for (int v = 0; v <= nums[0]; v++) {
      preSum[v] = v == 0 ? 1 : 1 + preSum[v - 1];
    }

    for (int i = 1; i < nums.size(); i++) {
      const int V1 = nums[i];
      const int V0 = nums[i - 1];
      vector<ll> tmpSum(maxVal, 0);

      for (int v = 0; v <= V1; v++) {
        if (V0 >= V1) {
          tmpSum[v] = v == 0 ? preSum[v] : preSum[v] + tmpSum[v - 1];
        } else {
          int minV = V1 - V0;
          if (v < minV) {
            continue;
          }
          tmpSum[v] = tmpSum[v - 1] + preSum[v - minV];
        }
        tmpSum[v] = tmpSum[v] % mod;
      }
      preSum.swap(tmpSum);
    }

    return preSum[nums.back()] % mod;
  }
};