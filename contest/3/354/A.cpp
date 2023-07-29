// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int sumOfSquares(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    for (int i = 1; i <= n; i++) {
      int v = nums[i - 1];
      if (n % i == 0) {
        ans += v * v;
      }
    }
    return ans;
  }
};