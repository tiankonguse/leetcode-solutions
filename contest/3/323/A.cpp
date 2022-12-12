// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int deleteGreatestValue(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid.front().size();
    for (auto& v : grid) {
      sort(v.begin(), v.end());
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
      int maxVal = grid[0][i];
      for (int j = 0; j < n; j++) {
        maxVal = max(maxVal, grid[j][i]);
      }
      ans += maxVal;
    }
    return ans;
  }
};