// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumAddedCoins(vector<int>& coins, int target) {
    sort(coins.begin(), coins.end());
    ll R = 0;
    int ans = 0;
    for (ll v : coins) {
      while (v > R + 1 && target > R) {
        ans++;
        R = R + R + 1;
      }
      R += v;
      if (target <= R) {
        break;
      }
    }
    while (target > R) {
      ans++;
      R = R + R + 1;
    }
    return ans;
  }
};