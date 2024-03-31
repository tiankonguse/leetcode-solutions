// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll countAlternatingSubarrays(vector<int> &nums) {
    ll ans = 0;
    int pre = nums.front();
    int k = 1;
    for (auto v : nums) {
      if (v == pre) {
        k = 1;
        ans++;
      } else {
        pre = v;
        k++;
        ans += k;
      }
    }
    return ans;
  }
};
