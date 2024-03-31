// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int dirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
class Solution {
 public:
  int minimumDistance(vector<vector<int>> &points) {
    int n = points.size();
    vector<vector<pair<int, int>>> nums(4, vector<pair<int, int>>(n));
    for (int i = 0; i < n; i++) {
      auto x = points[i][0], y = points[i][1];
      for (int k = 0; k < 4; k++) {
        nums[k][i] = {x * dirs[k][0] + y * dirs[k][1], i};
      }
    }

    for (int k = 0; k < 4; k++) {
      sort(nums[k].begin(), nums[k].end());
    }

    auto High = [&nums](int k, int pos) -> int {
      int n = nums[k].size();
      // printf("high n=%d k=%d pos=%d begin\n", n, k, pos);
      for (int i = n - 1; i >= 0; i--) {
        auto [v, p] = nums[k][i];
        if (p != pos) {
          return v;
        }
      }
      // printf("high k=%d pos=%d end\n", k, pos);
      return 0;
    };
    auto Low = [&nums](const int k, const int pos) -> int {
      // printf("low k=%d pos=%d begin\n", k, pos);
      int n = nums[k].size();
      for (int i = 0; i < n; i++) {
        auto [v, p] = nums[k][i];
        if (p != pos) {
          return v;
        }
      }
      // printf("low k=%d pos=%d end\n", k, pos);
      return 0;
    };

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
      int tmp = 0;
      for (int k = 0; k < 4; k++) {
        tmp = max(tmp, High(k, i) - Low(k, i));
      }
      ans = min(ans, tmp);
    }
    // printf("ans=%d\n", ans);
    return ans;
  }
};
