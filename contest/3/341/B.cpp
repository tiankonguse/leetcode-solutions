// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxDivScore(vector<int>& nums, vector<int>& divisors) {
    ll val = 0, num = -1;
    sort(divisors.begin(), divisors.end());
    for (auto v : divisors) {
      int sum = 0;
      for (auto V : nums) {
        if (V % v == 0) {
          sum++;
        }
      }
      if (sum > num) {
        num = sum;
        val = v;
      }
    }
    return val;
  }
};