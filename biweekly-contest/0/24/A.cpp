// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minStartValue(vector<int>& nums) {
    int minVal = 0;
    int preSum = 0;
    for (auto v : nums) {
      preSum += v;
      minVal = min(minVal, preSum);
    }
    return 1 - min(minVal, 0);
  }
};
