// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
    int n = grid.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int exceptVal = i * n + j;
        do {
          int oldVal = grid[i][j] - 1;
          if (oldVal == exceptVal) {
            break;
          }
          int x = oldVal / n;
          int y = oldVal % n;
          if (grid[i][j] == grid[x][y]) {
            break;
          }
          swap(grid[i][j], grid[x][y]);
        } while (1);
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int oldVal = grid[i][j] - 1;
        int exceptVal = i * n + j;
        if (oldVal != exceptVal) {
          return {oldVal + 1, exceptVal + 1};
        }
      }
    }
    return {};
  }
};
