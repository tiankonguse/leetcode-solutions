// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findChampion(vector<vector<int>>& grid) {
    int n = grid.size();
    for (int i = 0; i < n; i++) {
      int sum = 0;
      for (int j = 0; j < n; j++) {
        sum += grid[i][j];
      }
      if (sum + 1 == n) {
        return i;
      }
    }
    return 0;
  }
};