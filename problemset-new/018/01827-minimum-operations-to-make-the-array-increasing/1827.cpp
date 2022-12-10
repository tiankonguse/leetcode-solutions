// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minOperations(vector<int>& nums) {
    int ans = 0;
    int pre = -1;
    for (auto v : nums) {
      if (pre >= v) {
        ans += pre - v + 1;
        pre++;
      } else {
        pre = v;
      }
    }
    return ans;
  }
};
