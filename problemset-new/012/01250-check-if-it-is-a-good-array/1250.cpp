// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool isGoodArray(vector<int>& nums) {
    ll ans = nums.front();
    for (ll v : nums) {
      ans = gcd(ans, v);
    }
    return ans == 1;
  }
};