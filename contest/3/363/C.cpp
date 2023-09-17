// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxNumberOfAlloys(int n, int k, int budget,
                        vector<vector<int>>& composition, vector<int>& stock,
                        vector<int>& cost) {
    ll ans = 0;
    for (vector<int>& com : composition) {
      ll l = 0, r = budget / cost[0] + stock[0] + 2;
      while (l < r) {
        ll mid = (l + r) / 2;
        ll sum = 0;
        for (int i = 0; i < n; i++) {
          if (com[i] * mid > stock[i]) {
            sum += (com[i] * mid - stock[i]) * cost[i];
          }
        }
        if (sum <= budget) {  // 可以
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      ans = max(ans, l - 1);
    }
    return ans;
  }
};