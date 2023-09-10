// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfPoints(vector<vector<int>>& nums) {
    sort(nums.begin(), nums.end());
    int ans = 0;
    int pre = -1;
    for (auto& v : nums) {
      int a = v[0], b = v[1];
      pre = max(pre, a - 1);
      if (pre < b) {
        ans += b - pre;
      }
      pre = max(pre, b);
    }
    return ans;
  }
};