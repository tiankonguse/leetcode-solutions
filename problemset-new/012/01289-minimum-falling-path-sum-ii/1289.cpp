// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    if (n == 1) {
      return grid.front().front();
    }

    vector<pair<int, int>> pre;
    vector<pair<int, int>> now;
    for (int i = 0; i < n; i++) {
      pre.push_back({grid[0][i], i});
    }
    sort(pre.begin(), pre.end());

    for (int i = 1; i < n; i++) {
      now.clear();
      for (int j = 0; j < n; j++) {
        int tmp = grid[i][j] + pre[0].first;
        if (pre[0].second == j) {
          tmp = grid[i][j] + pre[1].first;
        }
        now.push_back({tmp, j});
      }
      now.swap(pre);
      sort(pre.begin(), pre.end());
    }
    return pre.front().first;
  }
};