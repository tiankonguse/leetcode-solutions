// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumOperationsToWriteY(vector<vector<int>>& grid) {
    int n = grid.size();
    const int c = n / 2;
    int Y[3] = {0, 0, 0};
    int Z[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        const int v = grid[i][j];
        if (i <= c) {
          if (i == j || i + j == n - 1) {
            Y[v]++;
          } else {
            Z[v]++;
          }
        } else {
          if (j == c) {
            Y[v]++;
          } else {
            Z[v]++;
          }
        }
      }
    }

    int sum_Y = 0;
    int sum_Z = 0;
    for (int i = 0; i < 3; i++) {
      sum_Y += Y[i];
      sum_Z += Z[i];
    }

    int ans = n * n;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (i == j) continue;
        int tmp = sum_Y - Y[i] + sum_Z - Z[j];
        ans = min(ans, tmp);
      }
    }
    return ans;
  }
};