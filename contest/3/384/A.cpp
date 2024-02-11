// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix.front().size();
    for (int i = 0; i < m; i++) {
      int maxVal = -1;
      for (int j = 0; j < n; j++) {
        maxVal = max(maxVal, matrix[j][i]);
      }
      for (int j = 0; j < n; j++) {
        if (matrix[j][i] == -1) {
          matrix[j][i] = maxVal;
        }
      }
    }
    return matrix;
  }
};