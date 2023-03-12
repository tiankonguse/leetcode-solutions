// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxScore(vector<int>& nums) {
    sort(nums.begin(), nums.end(), [](auto a, auto b) { return a > b; });
    ll sum = 0;
    ll ans = 0;
    for (auto v : nums) {
      sum += v;
      if (sum > 0) {
        ans++;
      } else {
        break;
      }
    }
    return ans;
  }
};