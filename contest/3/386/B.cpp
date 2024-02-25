// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long largestSquareArea(vector<vector<int>>& bottomLeft,
                              vector<vector<int>>& topRight) {
    int n = bottomLeft.size();
    ll ans = 0;
    auto fix = [&](int i) -> tuple<ll, ll, ll, ll> {
      ll L0 = bottomLeft[i][0];
      ll R0 = topRight[i][0];
      ll B0 = bottomLeft[i][1];
      ll T0 = topRight[i][1];
      return {L0, R0, B0, T0};
    };
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        auto [L0, R0, B0, T0] = fix(i);
        auto [L1, R1, B1, T1] = fix(j);
        if (B0 >= T1 || B1 >= T0) continue;  // 上下没有交集
        if (L0 >= R1 || L1 >= R0) continue;  // 上下没有交集

        ll T2 = min(T0, T1);
        ll L2 = max(L0, L1);
        ll B2 = max(B0, B1);
        ll R2 = min(R0, R1);

        ll r = min(T2 - B2, R2 - L2);
        if (r <= 0) continue;
        ans = max(ans, r * r);
      }
    }

    return ans;
  }
};