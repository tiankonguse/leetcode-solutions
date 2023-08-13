// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  int Solver(vector<vector<int>>& img1, vector<vector<int>>& img2) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int tmp1 = 0;
        int tmp2 = 0;
        int tmp3 = 0;
        int tmp4 = 0;
        for (int ii = 0; i + ii < n; ii++) {
          for (int jj = 0; j + jj < n; jj++) {
            if (img1[ii][jj] && img2[i + ii][j + jj]) tmp1++;  // 右下
          }
        }
        ans = max(ans, tmp1);
      }
    }

    return ans;
  }

  void FlapRow(vector<vector<int>>& img) {
    for (auto& v : img) {
      std::reverse(v.begin(), v.end());
    }
  }
  void FlapCol(vector<vector<int>>& img) {
    std::reverse(img.begin(), img.end());
  }

 public:
  int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
    n = img1.size();
    int ans = 0;
    ans = max(ans, Solver(img1, img2));  // 右下
    FlapRow(img1);
    FlapRow(img2);
    ans = max(ans, Solver(img1, img2));  // 左下
    FlapCol(img1);
    FlapCol(img2);
    ans = max(ans, Solver(img1, img2));  // 左上

    FlapRow(img1);
    FlapRow(img2);
    ans = max(ans, Solver(img1, img2));  // 左下

    return ans;
  }
};
