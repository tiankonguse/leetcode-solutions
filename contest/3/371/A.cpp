// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumStrongPairXor(vector<int>& nums) {
    int ans = 0;
    for (auto x : nums) {
      for (auto y : nums) {
        if (abs(x - y) <= min(x, y)) {
          ans = max(ans, x ^ y);
        }
      }
    }
    return ans;
  }
};
