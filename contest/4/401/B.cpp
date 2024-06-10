// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int valueAfterKSeconds(int n, int k) {
    vector<ll> nums(n + 1, 1);
    nums[0] = 0;
    while (k--) {
      for (int i = 1; i <= n; i++) {
        nums[i] = (nums[i] + nums[i - 1]) % mod;
      }
    }

    return nums.back();
  }
};