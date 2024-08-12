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
    vector<ll> preVal(maxVal, 0);
    vector<ll> preSum(maxVal, 0);
    for (int v = 0; v <= nums[0]; v++) {
      preVal[v] = 1;
      preSum[v] = v == 0 ? preVal[v] : preVal[v] + preSum[v - 1];
    }

    for (int i = 1; i < nums.size(); i++) {
      const int V1 = nums[i];
      const int V0 = nums[i - 1];
      vector<ll> tmpVal(maxVal, 0);
      vector<ll> tmpSum(maxVal, 0);

      for (int v = 0; v <= V1; v++) {
        if (V0 >= V1) {
          tmpVal[v] = preSum[v];
          tmpSum[v] = v == 0 ? tmpVal[v] : tmpVal[v] + tmpSum[v - 1];
        } else {
          int minV = V1 - V0;
          if (v < minV) {
            continue;
          }
          tmpVal[v] = preSum[v - minV];
          tmpSum[v] = tmpSum[v - 1] + tmpVal[v];
        }
        preSum[v] = preSum[v] % mod;
        tmpSum[v] = tmpSum[v] % mod;
      }
      preVal.swap(tmpVal);
      preSum.swap(tmpSum);
    }

    ll ans = 0;
    for (auto v : preVal) {
      ans = (ans + v) % mod;
    }
    return ans % mod;
  }
};