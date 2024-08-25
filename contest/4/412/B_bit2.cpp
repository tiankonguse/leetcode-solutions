// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int countPairs(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int v = __builtin_popcount(nums[i] ^ nums[j]);
        if (v == 0 || v == 2) {
          ans++;
        }
      }
    }

    return ans;
  }
};