// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minElements(vector<int>& nums, int limit, int goal) {
    ll sum = accumulate(nums.begin(), nums.end(), 0LL);
    ll dis = goal - sum;

    if (dis < 0) {
      dis = -dis;
    }

    return (dis + limit - 1) / limit;
  }
};