// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxTotalReward(vector<int>& rewardValues) {
    const int N = 2020;
    vector<ll> flags(N, 0);

    sort(rewardValues.begin(), rewardValues.end());
    flags[0] = 1;

    ll ans = 0;

    for (ll v : rewardValues) {
      for (int i = 0; i < v; i++) {
        if (flags[i]) {
          ll tmp = i + v;
          ans = max(ans, tmp);
          if (tmp < N) {
            flags[tmp] = 1;
          }
        }
      }
    }

    return ans;
  }
};