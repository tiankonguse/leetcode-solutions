// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfPairs(vector<vector<int>>& points) {
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
      if (a[0] == b[0]) {
        return a[1] > b[1];
      }
      return a[0] < b[0];
    });

    int n = points.size();
    auto get = [&points](int i) -> pair<int, int> {
      return {points[i][0], points[i][1]};
    };

    auto check = [&points, &get](int l, int r) -> bool {
      auto [x0, y0] = get(l);
      auto [x1, y1] = get(r);
      if (y0 < y1) return false;

      for (int i = l + 1; i < r; i++) {
        auto [x, y] = get(i);
        if (y <= y0 && y >= y1) return false;
      }
      return true;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (check(i, j)) {
          ans++;
        }
      }
    }

    return ans;
  }
};