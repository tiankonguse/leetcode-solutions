// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
    int X = mat.size();
    int Y = mat.front().size();
    unordered_map<int, pair<int, int>> h;
    for (int x = 0; x < X; x++) {
      for (int y = 0; y < Y; y++) {
        h[mat[x][y]] = {x, y};
      }
    }

    vector<int> rows(X, 0), cols(Y, 0);

    for (int i = 0; i < X * Y; i++) {
      auto [x, y] = h[arr[i]];
      rows[x]++;
      cols[y]++;
      if (rows[x] == Y) return i;
      if (cols[y] == X) return i;
    }
    return X * Y - 1;
  }
};