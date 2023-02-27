// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int largest1BorderedSquare(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid.front().size();
    vector<vector<int>> downMax(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> rightMax(n + 1, vector<int>(m + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        if (grid[i][j] == 1) {
          downMax[i][j] = downMax[i + 1][j] + 1;
          rightMax[i][j] = rightMax[i][j + 1] + 1;
        }
      }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int K = min(downMax[i][j], rightMax[i][j]);
        for (int k = 1; k <= K; k++) {
          int x = i + k - 1;
          int y = j + k - 1;
          if (rightMax[x][j] >= k && downMax[i][y] >= k) {
            ans = max(ans, k);
          }
        }
      }
    }
    return ans * ans;
  }
};