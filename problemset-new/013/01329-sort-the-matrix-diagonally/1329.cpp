// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> mat;
  vector<int> tmp;
  int n, m;
  void MySort(int x, int y) {
    tmp.clear();
    for (int i = x, j = y; i < n && j < m; i++, j++) {
      tmp.push_back(mat[i][j]);
    }
    sort(tmp.begin(), tmp.end());
    for (int i = x, j = y, k = 0; i < n && j < m; i++, j++, k++) {
      mat[i][j] = tmp[k];
    }
  }

 public:
  vector<vector<int>> diagonalSort(vector<vector<int>>& mat_) {
    mat.swap(mat_);

    n = mat.size();
    m = mat.front().size();
    for (int i = 0; i < n; i++) {
      MySort(i, 0);
    }
    for (int j = 1; j < m; j++) {
      MySort(0, j);
    }
    return mat;
  }
};
