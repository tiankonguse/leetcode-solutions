// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  ll maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
    int n = energyDrinkA.size();
    vector<int>* point[2] = {&energyDrinkA, &energyDrinkB};
    vector<vector<ll>> dp(2, vector<ll>(n, 0));
    auto H = [](vector<ll>& p, int i) -> ll {
      if (i < 0) return 0;
      return p.at(i);
    };
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        dp[j][i] = point[j]->at(i);
        dp[j][i] += max(H(dp[j], i - 1), H(dp[1 - j], i - 2));
      }
    }
    return max(dp[0].back(), dp[1].back());
  }
};

