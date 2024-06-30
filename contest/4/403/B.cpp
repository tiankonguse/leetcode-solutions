// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumArea(vector<vector<int>>& grid) {
    int top = 1000;
    int down = 0;
    int left = 1000;
    int right = 0;

    int n = grid.size();
    int m = grid.front().size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j]) {
          top = min(top, i);
          down = max(down, i);
          left = min(left, j);
          right = max(right, j);
        }
      }
    }
    return (down - top + 1) * (right - left + 1);
  }
};