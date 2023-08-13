// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
    int n = image.size();
    int m = image.front().size();
    for (int i = 0; i < n; i++) {
      int l = 0, r = m - 1;
      while (l < r) {
        swap(image[i][l], image[i][r]);
        l++, r--;
      }
      for (int j = 0; j < m; j++) {
        image[i][j] = 1 - image[i][j];
      }
    }
    return image;
  }
};
