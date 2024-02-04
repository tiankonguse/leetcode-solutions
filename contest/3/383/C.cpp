// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
    int n = image.size();
    int m = image.front().size();
    vector<vector<int>> parts(n, vector<int>(m, -1));

    auto CalPart = [&image, threshold](const int x, const int y) -> int {
      // 左右对比
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
          int X = x + i;
          int Y = y + j;
          if (abs(image[X][Y] - image[X][Y + 1]) > threshold) {
            return -1;
          }
        }
      }

      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
          int X = x + i;
          int Y = y + j;
          if (abs(image[X][Y] - image[X + 1][Y]) > threshold) {
            return -1;
          }
        }
      }

      int ans = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          ans += image[x + i][y + j];
        }
      }
      return ans / 9;
    };

    for (int i = 0; i + 3 <= n; i++) {
      for (int j = 0; j + 3 <= m; j++) {
        parts[i][j] = CalPart(i, j);
      }
    }

    auto CalAns = [&parts, &image](const int x, const int y) {
      int sum = 0;
      int num = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          const int X = x - i;
          const int Y = y - j;
          if (X < 0 || Y < 0) continue;
          if (parts[X][Y] == -1) continue;
          sum += parts[X][Y];
          num++;
        }
      }
      if (num == 0) {
        return image[x][y];
      } else {
        return sum / num;
      }
    };

    vector<vector<int>>& ans = image;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans[i][j] = CalAns(i, j);
      }
    }
    return ans;
  }
};