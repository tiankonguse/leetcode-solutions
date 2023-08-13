// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numMagicSquaresInside(vector<vector<int>>& grid) {
    int ans = 0;
    int n = grid.size();
    int m = grid.front().size();

    auto check = [&](int x, int y) {
      // printf("line=%d ", __LINE__);
      if (n - x < 3 || m - y < 3) {
        // printf("x=%d y=%d line=%d\n", x, y, __LINE__);
        return false;
      }

      int mask = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          mask |= 1 << grid[x + i][y + j];
        }
      }
      if ((mask + 2) != (1 << 10)) {
        // printf("x=%d y=%d line=%d\n", x, y, __LINE__);
        return false;
      }

      int sum = 0, tmp = 0;
      for (int i = 0; i < 3; i++) {
        sum += grid[x + i][y];
      }

      for (int i = 0; i < 3; i++) {
        tmp = 0;
        for (int j = 0; j < 3; j++) {
          tmp += grid[x + i][y + j];
        }
        if (tmp != sum) {
          // printf("x=%d y=%d line=%d\n", x, y, __LINE__);
          return false;
        }
      }

      for (int j = 0; j < 3; j++) {
        tmp = 0;
        for (int i = 0; i < 3; i++) {
          tmp += grid[x + i][y + j];
        }
        if (tmp != sum) {
          // printf("x=%d y=%d line=%d\n", x, y, __LINE__);
          return false;
        }
      }

      tmp = 0;
      for (int k = 0; k < 3; k++) {
        tmp += grid[x + k][y + k];
      }
      if (tmp != sum) {
        // printf("x=%d y=%d line=%d\n", x, y, __LINE__);
        return false;
      }

      tmp = 0;
      for (int k = 0; k < 3; k++) {
        tmp += grid[x + k][y + 2 - k];
      }
      if (tmp != sum) {
        // printf("x=%d y=%d line=%d\n", x, y, __LINE__);
        return false;
      }

        // printf("x=%d y=%d true line=%d\n", x, y, __LINE__);
      return true;
    };

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (check(i, j)) {
          ans++;
        }
      }
    }
    return ans;
  }
};