// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long minimumCost(int m, int n, vector<int>& horizontalCut,
                        vector<int>& verticalCut) {
    vector<pair<int, int>> H;
    H.reserve(m + n);
    for (auto v : horizontalCut) {
      H.push_back({v, 0});
    }
    for (auto v : verticalCut) {
      H.push_back({v, 1});
    }

    sort(H.begin(), H.end(), [](int a, int b) { return a > b; });

    ll ans = 0;
    ll numH = 1;
    ll numV = 1;
    for (auto [v, dir] : H) {
      if (dir == 0) {  // h 方向
        ans += numV * v;
        numH++;
      } else {
        ans += numH * v;
        numV++;
      }
    }
    return ans;
  }
};