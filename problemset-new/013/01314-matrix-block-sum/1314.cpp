// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
    int n = mat.size();
    int m = mat.front().size();

    vector<vector<int>> ans(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int x = max(i - k, 0); x <= min(i + k, n - 1); x++) {
          for (int y = max(j - k, 0); y <= min(j + k, m - 1); y++) {
            sum += mat[x][y];
          }
        }
        ans[i][j] = sum;
      }
    }
    return ans;
  }
};