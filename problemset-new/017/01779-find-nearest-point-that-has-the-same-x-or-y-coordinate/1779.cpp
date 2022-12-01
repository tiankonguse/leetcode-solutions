#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
    int ans = -1;
    int dis = 100000;

    for (int i = 0; i < points.size(); i++) {
      int X = points[i][0], Y = points[i][1];
      if (x == X || y == Y){
          int d = abs(y - Y) + abs(x - X);
          if (d < dis) {
            ans = i;
            dis = d;
          }
        }
    }
    return ans;
  }
};