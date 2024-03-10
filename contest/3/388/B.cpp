// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long maximumHappinessSum(vector<int>& happiness, int k) {
    sort(happiness.begin(), happiness.end(),
         [](auto& a, auto& b) { return a > b; });

    ll ans = 0;
    for (int i = 0; i < k; i++) {
      ans += max(happiness[i] - i, 0);
    }

    return ans;
  }
};